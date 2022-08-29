#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include "libft/libft.h"
/*
static void	action(int sig)
{
	static int	received = 0;

	if (sig == SIGUSR1)
		++received;
	else
	{
		ft_putnbr_fd(received, 1);
		ft_putchar_fd('\n', 1); 
		exit(0);
	}
}
static void	mt_kill(int pid, char *str)
{
	char	c;
	int		j = 128;       // 128 = 10000000 en bit, si / 2 -> 64 = 01000000 etc..
	char	new = 0;
	int		f = 0;
	int		i ;

	while (str[f])
	{
		c = str[f];
		while (j > 0)
		{								// >> mouvement de byte ver la droite 
			if ((c & j) > 0)
			{
				new = new | j;				// & -> compare les byte et renvoi les byte ou il y a 1 dans les deux
				kill(pid, SIGUSR2);
			}								// comment envoyer les lettres -> grasse a kill par byte
			else
				kill(pid, SIGUSR1);
			usleep(100);
			j /= 2;				// pour reduire le charge de travaille, pour que le programme puise faire certain cycle
		}
		new = 0;
		j = 128;
		f++;
	}
	i = 8;
	while (i--)						// combien de caractere reçu;
	{
		kill(pid, SIGUSR1);
		usleep(100);
	}
}

int	main(int argc, char **argv)
{
	if (argc != 3 || !ft_strlen(argv[2]))
		return (1);
	ft_putstr_fd("Sent    : ", 1);
	ft_putnbr_fd(ft_strlen(argv[2]), 1);
	ft_putchar_fd('\n', 1);
	ft_putstr_fd("Received: ", 1);
	signal(SIGUSR1, action);		// peut pas bloque les signales
	signal(SIGUSR2, action);
	mt_kill(ft_atoi(argv[1]), argv[2]);
	while (1)
		pause();
	return (0);
}*/
/*
void	send_bit_by_bit(int pid, char *argv)
{
	size_t	len;
	size_t	i;
	int		shift;

	len = ft_strlen(argv);
	i = 0;
	while (i < len)
	{
		shift = 0;
		while (shift < 8)
		{
			if ((argv[i] >> shift) & 1)
				kill(pid, SIGUSR2);
			else
				kill(pid, SIGUSR1);
			shift++;
			usleep(100);
		}
		i++;
	}
}*/

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
	}
	else
		write(1, "./client 'pid' 'message'\n", 25);
	return (0);
}


// https://www.youtube.com/watch?v=PErrlOx3LYE&list=RDCMUC6qj_bPq6tQ6hLwOBpBQ42Q&index=2

// https://www.youtube.com/watch?v=jF-1eFhyz1U&list=RDCMUC6qj_bPq6tQ6hLwOBpBQ42Q&index=3