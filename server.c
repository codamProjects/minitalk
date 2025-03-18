
#include "minitalk.h"

static void	signal_handler(int sig)
{
	static unsigned int	x;
	static int			i;

	i++;
	if (sig == SIGUSR1)
		x *= 2;
	else if (sig == SIGUSR2)
		x = (x * 2) + 1;
	if (i == 8)
	{
		if (x == 0)
			ft_printf("\n");
		else if (x > 0 && x < 128)
			ft_printf("%c", (unsigned char) x);
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
