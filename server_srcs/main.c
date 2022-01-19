/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: jvan-kra <jvan-kra@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/12/16 18:45:49 by jvan-kra      #+#    #+#                 */
/*   Updated: 2022/01/19 18:02:54 by jvan-kra      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

char	g_recstr[10000];

void	sigfunct(int sigid, siginfo_t *info, void *context)
{
	static int	bitcnt;
	static int	position;
	static char	buff;

	(void)context;
	if (sigid == SIGUSR1)
	{
		buff &= ~(1 << bitcnt);
	}
	else if (sigid == SIGUSR2)
	{
		buff |= 1 << bitcnt;
	}
	// printf("sending pid = %d\n", info->si_pid);
	if (bitcnt >= 7)
	{
		bitcnt = 0;
		if (buff == '\0' || position >= 9999)
		{
			printf("%s\n", g_recstr);
			position = 0;
			g_recstr[0] = 0;
		}
		else
		{
			g_recstr[position] = buff;
			g_recstr[position + 1] = 0;
			position++;
		}
	}
	else
		bitcnt++;
}

int	main(void)
{
	ft_printf("%d\n", getpid());
	g_recstr[0] = 0;
	struct sigaction sigstruct;
	ft_memset(&sigstruct, 0, sizeof(sigstruct));
	sigstruct.sa_sigaction = sigfunct;
	sigstruct.sa_flags = SA_SIGINFO;
	sigaction(SIGUSR1, &sigstruct, NULL);
	sigaction(SIGUSR2, &sigstruct, NULL);
	
	while (1)
	{
		sleep(1);
	}
}
