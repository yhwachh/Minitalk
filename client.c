#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include "libft/libft.h"

void	send_bit_by_bit(int pid, char *argv)
{
	size_t	j;
	size_t	i;
	int		move;

	j = ft_strlen(argv);
	i = 0;
	while (i < j)
	{
		move = 0;
		while (move < 8)
		{
			if ((argv[i] >> move) & 1)
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
		send_bit_by_bit(ft_atoi(argv[1]), argv[2]);
		send_bit_by_bit(ft_atoi(argv[1]), argv[write(1 , "\n", 2)]);
	}
	else
		write(1, "./client 'pid' 'message'\n", 25);
	return (0);
}