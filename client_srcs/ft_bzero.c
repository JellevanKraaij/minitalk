/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_bzero.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: jvan-kra <jvan-kra@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/19 15:42:49 by jvan-kra      #+#    #+#                 */
/*   Updated: 2022/01/25 17:42:55 by jvan-kra      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

void	*ft_memset(void *b, int c, size_t len)
{
	void	*_b;

	_b = b;
	while (len)
	{
		*(char *)b = c;
		b++;
		len--;
	}
	return (_b);
}

void	ft_bzero(void *s, size_t n)
{
	ft_memset(s, 0, n);
}
