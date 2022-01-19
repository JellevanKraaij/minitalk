/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_helpers.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: jvan-kra <jvan-kra@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/25 14:19:25 by jvan-kra      #+#    #+#                 */
/*   Updated: 2022/01/19 15:09:31 by jvan-kra      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

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

int	ft_hexlen(size_t num)
{
	int	length;

	length = 0;
	if (num == 0)
		return (1);
	while (num)
	{
		num /= 16;
		length++;
	}
	return (length);
}

int	ft_printfnrlen(long num)
{
	int	length;

	if (num == 0)
		return (1);
	length = 0;
	while (num)
	{
		num /= 10;
		length++;
	}
	return (length);
}

int	ft_my_atoi(const char **str)
{
	long	ret;

	ret = 0;
	while (**str >= '0' && **str <= '9')
	{
		ret = (ret * 10) + (**str - '0');
		(*str)++;
	}
	return (ret);
}
