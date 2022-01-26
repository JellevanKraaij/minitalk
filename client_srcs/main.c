/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: jvan-kra <jvan-kra@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/19 15:14:56 by jvan-kra      #+#    #+#                 */
/*   Updated: 2022/01/26 19:54:38 by jvan-kra      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

volatile int8_t	g_signal_received = 1;

void	pidcheck(int check)
{
	if (check == -1)
	{
		ft_putstr_fd("pid error, check if pid is correct\n", STDERR_FILENO);
		exit(1);
	}
}

void	sendbyte(int pid, const char *str)
{
	static const char	*_str;
	static int			_pid;
	static size_t		strcnt;
	static int8_t		bitcnt;

	if (pid != 0)
		_pid = pid;
	if (str != NULL)
		_str = str;
	if (_str[strcnt] & 1 << bitcnt)
		pidcheck(kill(_pid, SIGUSR2));
	else
		pidcheck(kill(_pid, SIGUSR1));
	bitcnt++;
	if (bitcnt > 7 && _str[strcnt] == '\0')
	{
		ft_putstr_fd("Message transmitted and received successfully!\n", \
		STDOUT_FILENO);
		exit(0);
	}
	if (bitcnt > 7)
	{
		bitcnt = 0;
		strcnt++;
	}
}

void	sighandler(int sigid)
{
	(void)sigid;
	g_signal_received = 1;
	sendbyte(0, NULL);
}

void	init_signals(void)
{
	struct sigaction	sigstruct;

	ft_bzero(&sigstruct, sizeof(sigstruct));
	sigstruct.sa_handler = sighandler;
	sigaction(SIGUSR1, &sigstruct, NULL);
}

int	main(int argc, char **argv)
{
	size_t	i;
	int		pid;

	i = 0;
	if (argc != 3 || ft_atoi_p(argv[1], &pid) != 0)
	{
		ft_putstr_fd("input error, usage ", STDOUT_FILENO);
		ft_putstr_fd(argv[0], STDOUT_FILENO);
		ft_putstr_fd(" [server pid] [string]\n", \
		STDERR_FILENO);
		exit(1);
	}
	init_signals();
	sendbyte(pid, argv[2]);
	while (1)
	{
		g_signal_received = 0;
		sleep(1);
		if (g_signal_received == 0)
		{
			ft_putstr_fd("error timeout occurred\n", STDERR_FILENO);
			exit(1);
		}
	}
}
