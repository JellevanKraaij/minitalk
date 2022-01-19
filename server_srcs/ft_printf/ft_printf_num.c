/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_printf_num.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: jvan-kra <jvan-kra@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/25 20:43:44 by jvan-kra      #+#    #+#                 */
/*   Updated: 2022/01/19 15:09:46 by jvan-kra      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

static void	ft_nr_print_prefx(long *num, t_flags flags)
{
	if (*num < 0 && (flags.zeropadd || flags.prec_cnt))
	{
		*num *= -1;
		ft_putchr('-');
	}
	else if (flags.addsign && *num >= 0)
		ft_putchr('+');
	else if (flags.addblk && *num >= 0)
		ft_putchr(' ');
}

static int	ft_cnt_nrlen(long num, t_flags flags, int numlen)
{
	int	len;

	len = numlen + (num < 0);
	if (flags.prec && flags.prec_cnt == 0 && num == 0)
		len--;
	if ((flags.addsign || flags.addblk) && num >= 0)
		len++;
	if (flags.prec_cnt - numlen > 0)
		len += flags.prec_cnt - numlen;
	return (len);
}

int	ft_printf_num(long num, t_flags flags)
{
	int	len;
	int	numlen;

	numlen = ft_printfnrlen(num);
	len = ft_cnt_nrlen(num, flags, numlen);
	if (flags.width > len && !flags.r_padd && (!flags.zeropadd || flags.prec))
		ft_padd(flags.width - len, ' ');
	ft_nr_print_prefx(&num, flags);
	if (flags.prec_cnt > numlen)
		ft_padd(flags.prec_cnt - numlen, '0');
	if (flags.width > len && !flags.r_padd && flags.zeropadd && !flags.prec)
		ft_padd(flags.width - len, '0');
	if (!flags.prec || flags.prec_cnt || num)
		ft_putnbr(num);
	if (flags.width > len && flags.r_padd)
		ft_padd(flags.width - len, ' ');
	if (flags.width > len)
		return (flags.width);
	return (len);
}
