/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niperez <niperez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 23:11:23 by niperez           #+#    #+#             */
/*   Updated: 2024/08/31 18:37:02 by niperez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static int	catch_int(char c, int *nb, char **message)
{
	if (c == '?')
	{
		if (*nb == 0)
			return (0);
		*message = malloc((*nb) + 1);
		if (!(*message))
			exit(1);
		return (1);
	}
	*nb = (10 * (*nb)) + (c - '0');
	return (0);
}

static int	catch_str(char c, int *nb, char **message)
{
	static int	index = 0;

	(*message)[index++] = c;
	if (index == *nb)
	{
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

static void	catch_message(int signal)
{
	static int	bit = 0;
	static char	c = 0;
	static int	state = 0;
	static int	nb = 0;
	static char	*message = NULL;

	if (signal == SIGUSR1)
		c |= (0x01 << bit);
	bit++;
	if (bit == 8)
	{
		if (!state)
			state = catch_int(c, &nb, &message);
		else
			state = catch_str(c, &nb, &message);
		bit = 0;
		c = 0;
	}
}

int	main(void)
{
	struct sigaction	sa;

	ft_bzero(&sa, sizeof(sa));
	sa.sa_handler = catch_message;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sigaddset(&sa.sa_mask, SIGUSR1);
	sigaddset(&sa.sa_mask, SIGUSR2);
	ft_printf("Server PID : %d\n", getpid());
	if (sigaction(SIGUSR1, &sa, NULL) == -1)
		return (1);
	if (sigaction(SIGUSR2, &sa, NULL) == -1)
		return (1);
	while (1)
		pause();
	return (0);
}
