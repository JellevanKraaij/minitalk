/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_printf_str.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: jvan-kra <jvan-kra@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/25 20:20:58 by jvan-kra      #+#    #+#                 */
/*   Updated: 2022/01/19 15:09:49 by jvan-kra      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

int	ft_printf_str(const char *str, t_flags flags)
{
	int	len;

	if (str == NULL)
		str = "(null)";
	len = ft_strlen(str);
	if (flags.prec && len > flags.prec_cnt)
		len = flags.prec_cnt;
	if (flags.width > len && !flags.r_padd)
		ft_padd(flags.width - len, ' ');
	ft_putnstr(str, len);
	if (flags.width > len && flags.r_padd)
		ft_padd(flags.width - len, ' ');
	if (flags.width > len)
		return (flags.width);
	return (len);
}
