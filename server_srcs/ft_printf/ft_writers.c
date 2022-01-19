/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_writers.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: jvan-kra <jvan-kra@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/25 12:19:14 by jvan-kra      #+#    #+#                 */
/*   Updated: 2022/01/19 15:09:55 by jvan-kra      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

void	ft_putchr(char c)
{
	write(1, &c, 1);
}

void	ft_putnstr(const char *str, int len)
{
	write(1, str, len);
}

void	ft_putnbr(long n)
{
	if (n < 0)
	{
		ft_putchr('-');
		n *= -1;
	}
	if (n > 9)
		ft_putnbr(n / 10);
	ft_putchr((n % 10) + '0');
}

void	ft_puthex(size_t n, int uppercase)
{
	const char	*charset;

	if (uppercase)
		charset = "0123456789ABCDEF";
	else
		charset = "0123456789abcdef";
	if (n > 15)
		ft_puthex(n / 16, uppercase);
	ft_putchr(charset[n % 16]);
}

void	ft_padd(int n, char paddchr)
{
	int	i;

	i = 0;
	while (i < n)
	{
		ft_putchr(paddchr);
		i++;
	}
}
