/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niperez <niperez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 23:11:37 by niperez           #+#    #+#             */
/*   Updated: 2024/08/30 21:08:03 by niperez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk_bonus.h"

static void	catch_confirm(int signal, siginfo_t *info, void *context)
{
	(void)signal;
	(void)info;
	(void)context;
	ft_printf("Message received !\n");
	exit(0);
}

static void	send_str(int pid, const char *str)
{
	int		bit;
	char	c;

	while (*str)
	{
		bit = 0;
		c = *str;
		while (bit < 8)
		{
			if (c & (0x01 << bit))
				kill(pid, SIGUSR1);
			else
				kill(pid, SIGUSR2);
			usleep(TIME_BUF);
			bit++;
		}
		str++;
	}
}

static void	send_int(int pid, const int nb)
{
	char	*size;

	size = ft_itoa(nb);
	if (size == NULL)
		exit(1);
	send_str(pid, size);
	free(size);
}

int	main(int argc, char **argv)
{
	int					pid_server;
	struct sigaction	sa;

	ft_bzero(&sa, sizeof(sa));
	sa.sa_sigaction = catch_confirm;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_SIGINFO | SA_RESTART;
	if (argc != 3)
		return (1);
	if (sigaction(SIGUSR1, &sa, NULL) == -1)
		return (1);
	pid_server = ft_atoi(argv[1]);
	ft_printf("Size message sent : %d\n", ft_strlen(argv[2]));
	send_int(pid_server, ft_strlen(argv[2]));
	send_str(pid_server, "?");
	send_str(pid_server, argv[2]);
	while (1)
		pause();
	return (0);
}
