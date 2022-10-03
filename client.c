/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibalbako <ibalbako@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/29 12:27:35 by ibalbako          #+#    #+#             */
/*   Updated: 2022/08/29 12:28:12 by ibalbako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	s_bit_by_bit(int pid, char *str)
{
	unsigned long	j;
	unsigned long	i;
	int				move;

	j = ft_strlen(str);
	i = 0;
	while (i < j)
	{
		move = 0;
		while (move < 8)
		{
			if ((str[i] >> move) & 1)
				kill(pid, SIGUSR2);
			else
				kill(pid, SIGUSR1);
			move++;
			usleep(100);
		}
		i++;
	}
}

int	main(int argc, char **argv)
{
	if (argc == 3)
	{
		s_bit_by_bit(ft_atoi(argv[1]), argv[2]);
		s_bit_by_bit(ft_atoi(argv[1]), "\n");
	}
	else
		write(1, "Need : ./client 'pid' 'message'\n", 32);
	return (0);
}
