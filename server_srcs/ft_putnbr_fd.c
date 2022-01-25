/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_putnbr_fd.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: jvan-kra <jvan-kra@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/19 15:44:24 by jvan-kra      #+#    #+#                 */
/*   Updated: 2022/01/25 17:45:37 by jvan-kra      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}

long	ft_nrlen(long input)
{
	int	length;

	length = 0;
	if (input == 0)
		return (1);
	if (input < 0)
		length++;
	while (input)
	{
		input /= 10;
		length++;
	}
	return (length);
}

double	ft_pow(double x, double y)
{
	double	ret;

	ret = 1;
	while (y > 0)
	{
		ret *= x;
		y--;
	}
	while (y < 0)
	{
		ret /= x;
		y++;
	}
	return (ret);
}

void	ft_putnbr_fd(int n, int fd)
{
	int		len;
	long	nb_long;

	nb_long = n;
	if (nb_long < 0)
	{
		ft_putchar_fd('-', fd);
		nb_long *= -1;
	}
	len = ft_nrlen(nb_long);
	while (len > 0)
	{
		ft_putchar_fd(((long)(nb_long / ft_pow(10, len - 1)) % 10) + '0', fd);
		len--;
	}
}
