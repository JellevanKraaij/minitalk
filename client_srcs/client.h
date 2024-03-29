/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   client.h                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: jvan-kra <jvan-kra@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/12/16 15:36:02 by jvan-kra      #+#    #+#                 */
/*   Updated: 2022/01/25 17:53:14 by jvan-kra      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENT_H
# define CLIENT_H
# include <unistd.h>
# include <signal.h>
# include <limits.h>
# include <stdlib.h>

void	ft_putstr_fd(char *s, int fd);
int		ft_atoi_p(const char *str, int *number);
void	ft_bzero(void *s, size_t n);

#endif