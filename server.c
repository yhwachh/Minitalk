#include <signal.h>
#include <unistd.h>
#include "libft/libft.h"
/*
static void	action(int sig, siginfo_t *info, void *context) // 1) numereau de signal 2) la structure 3) osef
{
	static int				i = 0;
	static pid_t			client_pid = 0;
	static unsigned char	c = 0;

	(void)context;   // osef
	if (!client_pid)
		client_pid = info->si_pid;		// 																	typedef struct {
	c |= (sig == SIGUSR2);				//	(sur deux byte mes 1 si il ya au moin un 1 dans l'un des deux )	pid_t si_pid ; (pross id) il contient le numereau du signal reçu , il remplit auto
	if (++i == 8)						//																	} siginfo_t
	{
		i = 0;
		if (!c)
		{
			kill(client_pid, SIGUSR2);
			client_pid = 0;
			return ;
		}
		ft_putchar_fd(c, 1);
		c = 0;
		kill(client_pid, SIGUSR1);
	}
	else
		c <<= 1;
}

void	handler(int signum, struct __siginfo *info, void *vo);

int	main(void)
{
	struct sigaction	s_sigaction;

	ft_putstr_fd("Server PID: ", 1);
	ft_putnbr_fd(getpid(), 1);
	ft_putchar_fd('\n', 1);
	s_sigaction.sa_sigaction = handler;		// ordre quand um signal passe par cette strusture , il dois le renvoyer ver la foction action
	s_sigaction.sa_flags = SA_SIGINFO;		// elle permet a la foction d'avoir 3 parametre si non compile pas
	sigaction(SIGUSR1, &s_sigaction, 0);	// peut bloque les signal , sigation stucture se trouve dans le header 
	sigaction(SIGUSR2, &s_sigaction, 0);	// pour defenir quel signal passe (signalName) par quel structure(structName)  
	while (1)
		pause();
	return (0);
}*/


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