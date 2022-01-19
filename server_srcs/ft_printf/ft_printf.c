/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_printf.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: jvan-kra <jvan-kra@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/21 16:45:14 by jvan-kra      #+#    #+#                 */
/*   Updated: 2022/01/19 15:09:51 by jvan-kra      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

static void	ft_printf_process_flag(const char **str, t_flags *flags)
{
	while ((**str == '#' || **str == ' ' || **str == '+' \
	|| **str == '-' || **str == '0'))
	{
		if (**str == '#')
			flags->add0x = 1;
		else if (**str == ' ')
			flags->addblk = 1;
		else if (**str == '+')
			flags->addsign = 1;
		else if (**str == '-')
			flags->r_padd = 1;
		else if (**str == '0')
			flags->zeropadd = 1;
		(*str)++;
	}
	if (**str >= '1' && **str <= '9')
		flags->width = ft_my_atoi(str);
	if (**str == '.')
	{
		(*str)++;
		flags->prec = 1;
		flags->prec_cnt = ft_my_atoi(str);
	}
	return ;
}

static void	ft_printf_process_spec(const char **str, va_list args, int *cnt)
{
	t_flags	flags;

	(*str)++;
	ft_printf_process_flag(str, ft_memset(&flags, 0, sizeof(t_flags)));
	if (**str == '%')
		*cnt += ft_printf_char('%', flags);
	else if (**str == 'c')
		*cnt += ft_printf_char(va_arg(args, int), flags);
	else if (**str == 's')
		*cnt += ft_printf_str(va_arg(args, char *), flags);
	else if (**str == 'i' || **str == 'd')
		*cnt += ft_printf_num((int)va_arg(args, int), flags);
	else if (**str == 'u')
		*cnt += ft_printf_num((unsigned int)va_arg(args, unsigned int), flags);
	else if (**str == 'x' || **str == 'X')
		*cnt += ft_printf_hex((unsigned int)va_arg(args, unsigned int), \
		**str, flags);
	else if (**str == 'p')
		*cnt += ft_printf_hex((size_t)va_arg(args, size_t), **str, flags);
	else
		return ;
	(*str)++;
	return ;
}

static int	ft_printf_process_str(const char *str, va_list args)
{
	int	chr_cnt;

	chr_cnt = 0;
	while (*str)
	{
		if (*str == '%')
			ft_printf_process_spec(&str, args, &chr_cnt);
		else
		{
			ft_putchr(*str);
			str++;
			chr_cnt++;
		}
	}
	return (chr_cnt);
}

int	ft_printf(const char *str, ...)
{
	va_list	args;
	int		chr_cnt;

	if (str == NULL)
		return (-1);
	va_start(args, str);
	chr_cnt = ft_printf_process_str(str, args);
	va_end(args);
	return (chr_cnt);
}
