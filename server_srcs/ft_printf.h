/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_printf.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: jvan-kra <jvan-kra@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/26 13:18:31 by jvan-kra      #+#    #+#                 */
/*   Updated: 2022/01/17 16:06:17 by jvan-kra      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include <stdarg.h>
# include <unistd.h>
# include <stddef.h>

typedef struct ft_printf_flags {
	int	add0x;
	int	addblk;
	int	addsign;
	int	width;
	int	r_padd;
	int	zeropadd;
	int	prec;
	int	prec_cnt;
}	t_flags;

int		ft_printf(const char *str, ...);

int		ft_printf_char(char c, t_flags flags);
int		ft_printf_str(const char *str, t_flags flags);
int		ft_printf_num(long num, t_flags flags);
int		ft_printf_hex(size_t num, char c, t_flags flags);
//helper functions

void	ft_putchr(char c);
void	ft_putnstr(const char *str, int len);
void	ft_putnbr(long n);
void	ft_puthex(size_t n, int uppercase);
size_t	ft_strlen(const char *s);
void	*ft_memset(void *b, int c, size_t len);
void	ft_padd(int n, char paddchr);
int		ft_printfnrlen(long num);
int		ft_hexlen(size_t num);
int		ft_my_atoi(const char **str);
#endif