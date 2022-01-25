/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: jvan-kra <jvan-kra@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/12/16 18:45:49 by jvan-kra      #+#    #+#                 */
/*   Updated: 2022/01/25 17:51:35 by jvan-kra      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

volatile char	*g_recstr;

void	decodesig(int signal, uint8_t bitcnt, size_t strcnt)
{
	if (signal == SIGUSR1)
		g_recstr[strcnt] &= ~(1 << bitcnt);
	else if (signal == SIGUSR2)
		g_recstr[strcnt] |= 1 << bitcnt;
}

void	sighandler(int signal, siginfo_t *info, void *context)
{
	volatile static int		bitcnt;
	volatile static size_t	strcnt;

	(void)context;
	decodesig(signal, bitcnt, strcnt);
	bitcnt++;
	if (bitcnt > 7)
	{
		bitcnt = 0;
		if (strcnt > BUFFER_SIZE - 1)
		{
			write(STDOUT_FILENO, (char *)g_recstr, strcnt);
			strcnt = 0;
		}
		else if (g_recstr[strcnt] == 0)
		{
			write(STDOUT_FILENO, (char *)g_recstr, strcnt);
			strcnt = 0;
		}
		else
			strcnt++;
	}
	kill(info->si_pid, SIGUSR1);
}

void	printpid(char *filename)
{
	ft_putstr_fd("[", STDOUT_FILENO);
	ft_putstr_fd(filename, STDOUT_FILENO);
	ft_putstr_fd("] pid = ", STDOUT_FILENO);
	ft_putnbr_fd(getpid(), STDOUT_FILENO);
	ft_putstr_fd("\n", STDOUT_FILENO);
}

void	init_signals(void)
{
	struct sigaction	sigstruct;

	ft_bzero(&sigstruct, sizeof(sigstruct));
	sigstruct.sa_sigaction = sighandler;
	sigstruct.sa_flags = SA_NODEFER | SA_SIGINFO;
	sigaction(SIGUSR1, &sigstruct, NULL);
	sigaction(SIGUSR2, &sigstruct, NULL);
}

int	main(int argc, char **argv)
{
	if (argc != 1)
	{
		ft_putstr_fd("input error usage ./server (no params)", STDERR_FILENO);
		exit(1);
	}
	printpid(argv[0]);
	g_recstr = malloc(BUFFER_SIZE);
	if (g_recstr == NULL)
		exit(1);
	init_signals();
	while (1)
	{
		sleep(100);
	}
}
