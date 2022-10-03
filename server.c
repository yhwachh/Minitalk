/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibalbako <ibalbako@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/29 12:28:39 by ibalbako          #+#    #+#             */
/*   Updated: 2022/08/29 12:29:26 by ibalbako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	g_bit_by_bit(int sig)
{
	static int				size = 0;
	static unsigned char	msg = 0;

	size++;
	msg = msg >> 1;
	if (sig == SIGUSR2)
		msg = msg | 128;
	if (size == 8)
	{
		write(1, &msg, 1);
		size = 0;
	}
}

int	main(void)
{
	struct sigaction	s_sigaction;

	s_sigaction.sa_flags = SA_SIGINFO;
	s_sigaction.sa_handler = &g_bit_by_bit;
	sigaction(SIGUSR1, &s_sigaction, NULL);
	sigaction(SIGUSR2, &s_sigaction, NULL);
	ft_putstr_fd("Process ID is ", 1);
	ft_putnbr_fd(getpid(), 1);
	write(1, "\n", 1);
	while (1)
		pause();
	return (0);
}
