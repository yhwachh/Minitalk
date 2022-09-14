#include <signal.h>
#include <unistd.h>
#include "libft/libft.h"

void	get_bit_by_bit(int sig)
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
	struct sigaction	sa;

	sa.sa_flags = SA_SIGINFO;
	sa.sa_handler = &get_bit_by_bit;
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	ft_putstr_fd("Process ID is ", 1);
	ft_putnbr_fd(getpid(), 1);
	write(1, "\n", 1);
	while (1)
		pause();
	return (0);
}