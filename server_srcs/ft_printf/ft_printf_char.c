/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_printf_char.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: jvan-kra <jvan-kra@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/25 15:32:01 by jvan-kra      #+#    #+#                 */
/*   Updated: 2022/01/19 15:09:39 by jvan-kra      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

int	ft_printf_char(char c, t_flags flags)
{
	if (flags.width > 1 && !flags.r_padd && flags.zeropadd)
		ft_padd(flags.width - 1, '0');
	else if (flags.width > 1 && !flags.r_padd)
		ft_padd(flags.width - 1, ' ');
	ft_putchr(c);
	if (flags.width > 1 && flags.r_padd)
		ft_padd(flags.width - 1, ' ');
	if (flags.width)
		return (flags.width);
	return (1);
}
