/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: jvan-kra <jvan-kra@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/19 15:14:56 by jvan-kra      #+#    #+#                 */
/*   Updated: 2022/01/19 18:00:15 by jvan-kra      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"
#include <stdio.h>

void	send_str(const char *str, pid_t pid)
{
	int		bitcnt;
	size_t	strcnt;

	strcnt = 0;
	while (str[strcnt])
	{
		bitcnt = 0;
		while (bitcnt < 8)
		{
			if (str[strcnt] & 1 << bitcnt)
				kill(pid, SIGUSR2);
			else
				kill(pid, SIGUSR1);
			usleep(10);
			bitcnt++;
		}
		strcnt++;
	}
	bitcnt = 0;
	while (bitcnt < 8)
	{
		kill(pid, SIGUSR1);
		bitcnt++;
		usleep(10);
	}
}

int	main(int argc, char **argv)
{
	size_t	i;

	i = 0;
	printf("cliendpid %d\n", getpid());
	if (argc != 3)
	{
		ft_putstr_fd("input error", 2);
		exit(1);
	}
	while (argv[1][i])
	{
		if (!ft_isdigit(argv[1][i]))
		{
			ft_putstr_fd("input error", 2);
			exit(1);
		}
		i++;
	}
	printf("pid=%d\n", ft_atoi(argv[1]));
	send_str(argv[2], ft_atoi(argv[1]));
}
