
#include "minitalk.h"

static void	ft_error_free(char *str, int x)
{
	if (x == 1)
	{
		if (str)
			free (str);
		exit (1);
	}
	else if (x == 0)
	{
		if (str)
			free (str);
	}
}

static void	ft_send_signal(char *str, int s_pid)
{
	int	i;

	i = 0;
	while (str && str[i])
	{
		if (str[i] == '0' && kill(s_pid, SIGUSR1) < 0)
			ft_error_free(str, 1);
		else if (str[i] == '1' && kill(s_pid, SIGUSR2) < 0)
			ft_error_free(str, 1);
		i++;
		usleep(200);
	}
	i = 0;
	while (i < 8)
	{
		if (kill(s_pid, SIGUSR1) < 0)
			ft_error_free(str, 1);
		i++;
		usleep(200);
	}
}

static char	*ft_get_binary(char *str)
{
	int				len;
	int				blen;
	char			*binstr;
	unsigned int	c;

	len = (int) ft_strlen(str);
	blen = len * 8;
	binstr = (char *) malloc((blen + 1) * sizeof(char));
	if (!binstr)
		return (NULL);
	binstr[blen] = '\0';
	while (str && --len >= 0 && str[len])
	{
		c = (unsigned int)(unsigned char)str[len];
		while (c > 0 || (blen % 8) != 0)
		{
			if ((c % 2) == 1)
				binstr[--blen] = '1';
			else
				binstr[--blen] = '0';
			c /= 2;
		}
	}
	return (binstr);
}

int	main(int argc, char *argv[])
{
	char	*str;
	int		s_pid;

	if (argc != 3 || ft_strlen(argv[2]) == 0 || ft_is_int(argv[1]) == 0)
		exit (1);
	str = ft_get_binary(argv[2]);
	if (!str)
		exit(1);
	s_pid = ft_atoi(argv[1]);
	ft_send_signal(str, s_pid);
	ft_error_free(str, 0);
	return (0);
}
