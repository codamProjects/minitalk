
#include "minitalk.h"

static int	ft_send_message_back(unsigned int x)
{
	static unsigned int	pid;

	if (x != 0)
	{
		pid = (pid * 10 + ((unsigned char) x - 48));
		return (1);
	}
	else
	{
		if (kill(pid, SIGUSR1) < 0)
		{
			pid = 0;
			exit (1);
		}
		pid = 0;
		usleep(1);
		return (0);
	}
}

static void	signal_handler(int sig)
{
	static unsigned int	x;
	static int			i;
	static int			p;

	i++;
	if (sig == SIGUSR1)
		x *= 2;
	else if (sig == SIGUSR2)
		x = (x * 2) + 1;
	if (i == 8)
	{
		if (x == 0 && p == 0)
		{
			ft_printf("\n");
			p = 1;
		}
		else if (p == 0 && x != 0)
			ft_printf("%c", (unsigned char) x);
		else if (p == 1)
			p = ft_send_message_back(x);
		x = 0;
		i = 0;
	}
}

int	main(void)
{
	int			pid;

	signal(SIGUSR1, signal_handler);
	signal(SIGUSR2, signal_handler);
	pid = getpid();
	ft_printf("%d\n", pid);
	while (1)
		pause();
	return (0);
}
