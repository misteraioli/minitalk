/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niperez <niperez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 23:11:23 by niperez           #+#    #+#             */
/*   Updated: 2024/09/02 15:44:11 by niperez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk_bonus.h"

static int	catch_int(char c, int *nb, char **message, siginfo_t *info)
{
	if (c == '?')
	{
		if (*nb == 0)
		{
			kill(info->si_pid, SIGUSR1);
			return (0);
		}
		*message = malloc((*nb) + 1);
		if (!(*message))
			exit(1);
		return (1);
	}
	*nb = (10 * (*nb)) + (c - '0');
	return (0);
}

static int	catch_str(char c, int *nb, char **message, siginfo_t *info)
{
	static int	index = 0;

	(*message)[index++] = c;
	if (index == *nb)
	{
		kill(info->si_pid, SIGUSR1);
		(*message)[index] = '\0';
		*nb = 0;
		index = 0;
		ft_printf("%s", *message);
		free(*message);
		*message = NULL;
		return (0);
	}
	return (1);
}

static void	catch_message(int signal, siginfo_t *info, void *context)
{
	static int	bit = 0;
	static char	c = 0;
	static int	state = 0;
	static int	nb = 0;
	static char	*message = NULL;

	(void)context;
	if (signal == SIGUSR1)
		c |= (0x01 << bit);
	bit++;
	if (bit == 8)
	{
		if (!state)
			state = catch_int(c, &nb, &message, info);
		else
			state = catch_str(c, &nb, &message, info);
		bit = 0;
		c = 0;
	}
}

int	main(void)
{
	struct sigaction	sa;

	ft_bzero(&sa, sizeof(sa));
	sa.sa_sigaction = catch_message;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_SIGINFO | SA_RESTART;
	ft_printf("Server PID : %d\n", getpid());
	if (sigaction(SIGUSR1, &sa, NULL) == -1)
		return (1);
	if (sigaction(SIGUSR2, &sa, NULL) == -1)
		return (1);
	while (1)
		pause();
	return (0);
}
