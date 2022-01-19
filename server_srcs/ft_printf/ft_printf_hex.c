/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_printf_hex.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: jvan-kra <jvan-kra@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/26 12:57:24 by jvan-kra      #+#    #+#                 */
/*   Updated: 2022/01/19 15:09:42 by jvan-kra      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

static void	ft_hex_print_prefx(size_t num, char c, t_flags flags)
{
	if (flags.addsign)
		ft_putchr('+');
	else if (flags.addblk)
		ft_putchr(' ');
	if ((flags.add0x && c == 'X' && num != 0))
		ft_putnstr("0X", 2);
	else if ((flags.add0x && num != 0) || c == 'p')
		ft_putnstr("0x", 2);
}

static int	ft_cnt_hexlen(size_t num, char c, t_flags flags, int hexlen)
{
	int	len;

	len = hexlen;
	if (flags.prec && flags.prec_cnt == 0 && num == 0)
		len--;
	if (flags.prec_cnt - hexlen > 0)
		len += flags.prec_cnt - hexlen;
	if ((flags.add0x && num != 0) || c == 'p')
		len += 2;
	if (flags.addsign || flags.addblk)
		len++;
	return (len);
}

int	ft_printf_hex(size_t num, char c, t_flags flags)
{
	int	len;
	int	hexlen;

	hexlen = ft_hexlen(num);
	len = ft_cnt_hexlen(num, c, flags, hexlen);
	if (flags.width > len && !flags.r_padd && (!flags.zeropadd || flags.prec))
		ft_padd(flags.width - len, ' ');
	ft_hex_print_prefx(num, c, flags);
	if (flags.prec_cnt > hexlen)
		ft_padd(flags.prec_cnt - hexlen, '0');
	if (flags.width > len && !flags.r_padd && flags.zeropadd && !flags.prec)
		ft_padd(flags.width - len, '0');
	if (!flags.prec || flags.prec_cnt || num)
		ft_puthex(num, c == 'X');
	if (flags.width && flags.r_padd)
		ft_padd(flags.width - len, ' ');
	if (flags.width > len)
		return (flags.width);
	return (len);
}
