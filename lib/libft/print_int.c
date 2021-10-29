/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   print_int.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: kde-wint <kde-wint@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/08/17 14:53:36 by kde-wint      #+#    #+#                 */
/*   Updated: 2021/08/04 17:25:30 by kde-wint      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft_internals.h"
#include <stdlib.h>

static void			print_direct(t_argprops *props, char c, int *written)
{
	putnstr_w(props->writer, &c, 1);
	(*written)++;
}

static void			print_int_prefix(
	t_argprops *props, int *written, long long ll, char **str)
{
	char	padchar;

	padchar = (props->flags & FLAG_ZERO && !(props->flags & FLAG_MINUS) &&
		!(props->flags & FLAG_PRECIS)) ? '0' : ' ';
	if (**str == '-')
		ft_strreplace(str, ft_strdup(*str + 1));
	while (props->flags & FLAG_PRECIS &&
		(int)ft_strlen(*str) < props->precision)
		ft_strreplace(str, ft_strjoin("0", *str));
	*written = ft_strlen(*str);
	if (ll < 0 || props->flags & FLAG_PLUS || props->flags & FLAG_SPACE)
		(*written)++;
	if (props->flags & FLAG_MINFW && !(props->flags & FLAG_MINUS) &&
		padchar == ' ')
		while (*written < props->minfw)
			print_direct(props, padchar, written);
	if (ll < 0)
		putnstr_w(props->writer, "-", 1);
	else if (props->flags & FLAG_PLUS)
		putnstr_w(props->writer, "+", 1);
	else if (props->flags & FLAG_SPACE)
		putnstr_w(props->writer, " ", 1);
	while (props->flags & FLAG_MINFW && !(props->flags & FLAG_MINUS) &&
		*written < props->minfw && padchar == '0')
		print_direct(props, padchar, written);
}

static long long	get_va_arg(t_argprops *props, va_list args)
{
	if (props->convtype == CONV_CHAR_INT)
		return ((long long)(char)va_arg(args, int));
	if (props->convtype == CONV_SHORT_INT)
		return ((long long)(short int)va_arg(args, int));
	if (props->convtype == CONV_INT)
		return ((long long)va_arg(args, int));
	if (props->convtype == CONV_LONG_INT)
		return ((long long)va_arg(args, long));
	else
		return (va_arg(args, long long));
}

void				print_int(t_argprops *props, va_list args, t_writer *writer)
{
	long long	ll;
	char		*str;
	int			written_loc;

	ll = get_va_arg(props, args);
	if (ll == (long long)0 && props->flags & FLAG_PRECIS &&
		props->precision == 0)
		str = ft_strdup("");
	else
		str = ft_lltoa_base(ll, 10);
	print_int_prefix(props, &written_loc, ll, &str);
	putnstr_w(writer, str, ft_strlen(str));
	ft_strdel(&str);
	while (props->flags & FLAG_MINFW && props->flags & FLAG_MINUS &&
		written_loc < props->minfw)
		print_direct(props, ' ', &written_loc);
}
