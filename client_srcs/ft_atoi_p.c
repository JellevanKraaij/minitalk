/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_atoi_p.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: jvan-kra <jvan-kra@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/25 16:16:46 by jvan-kra      #+#    #+#                 */
/*   Updated: 2022/01/26 19:38:25 by jvan-kra      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

int	ft_isdigit(int c)
{
	return (c >= '0' && c <= '9');
}

int	ft_atoi_p(const char *str, int *number)
{
	int		sign;
	long	ret;

	ret = 0;
	sign = 1;
	if (*str == '-')
	{
		sign = -1;
		str++;
	}
	else if (*str == '+')
		str++;
	while (ft_isdigit(*str))
	{
		ret = (ret * 10) + (*str - '0');
		if (ret > INT_MAX || (sign == -1 && ret > INT_MAX - 1))
			return (-1);
		str++;
	}
	if (*str != '\0')
		return (-1);
	ret *= sign;
	*number = (int)ret;
	return (0);
}
