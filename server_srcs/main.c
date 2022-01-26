/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: jvan-kra <jvan-kra@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/12/16 18:45:49 by jvan-kra      #+#    #+#                 */
/*   Updated: 2022/01/26 19:48:20 by jvan-kra      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

volatile t_state	g_state;

int	decodesig(int signal, char *ret)
{
	static char		buf;
	static int		bitcnt;

	if (ret == NULL)
	{
		bitcnt = 0;
		return (1);
	}
	if (signal == SIGUSR1)
		buf &= ~(1 << bitcnt);
	else if (signal == SIGUSR2)
		buf |= 1 << bitcnt;
	bitcnt++;
	if (bitcnt > 7)
	{
		*ret = buf;
		bitcnt = 0;
		return (1);
	}
	return (0);
}

int	printchar(char rchar)
{
	static size_t	strcnt;
	static char		*buffer;

	if (buffer == NULL)
		buffer = malloc(BUFFER_SIZE);
	if (buffer == NULL)
		exit(1);
	buffer[strcnt] = rchar;
	if (strcnt > BUFFER_SIZE - 1)
	{
		write(STDOUT_FILENO, buffer, strcnt + 1);
		strcnt = 0;
		return (0);
	}
	if (buffer[strcnt] == 0)
	{
		write(STDOUT_FILENO, buffer, strcnt);
		strcnt = 0;
		free(buffer);
		buffer = NULL;
		return (1);
	}
	strcnt++;
	return (0);
}

void	sighandler(int signal, siginfo_t *info, void *context)
{
	char	rchar;

	(void)context;
	g_state.sigrec = 1;
	g_state.idle = 0;
	if (decodesig(signal, &rchar) && printchar(rchar))
		g_state.idle = 1;
	if (kill(info->si_pid, SIGUSR1) == -1)
	{
		decodesig(0, NULL);
		printchar(0);
		ft_putstr_fd("\nclient exited, flushed buffer\n", \
		STDERR_FILENO);
		g_state.idle = 1;
	}
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
	ft_putstr_fd("[", STDOUT_FILENO);
	ft_putstr_fd(argv[0], STDOUT_FILENO);
	ft_putstr_fd("] pid = ", STDOUT_FILENO);
	ft_putnbr_fd(getpid(), STDOUT_FILENO);
	ft_putstr_fd("\n", STDOUT_FILENO);
	g_state.idle = 1;
	init_signals();
	while (1)
	{
		g_state.sigrec = 0;
		sleep(1);
		if (g_state.sigrec == 0 && g_state.idle == 0)
		{
			decodesig(0, NULL);
			printchar(0);
			ft_putstr_fd("\nerror timeout occurred flushed buffer\n", \
			STDERR_FILENO);
			g_state.idle = 1;
		}
	}
}
