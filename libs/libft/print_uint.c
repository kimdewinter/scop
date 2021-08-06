/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   print_uint.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: kde-wint <kde-wint@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/09 12:27:31 by kde-wint      #+#    #+#                 */
/*   Updated: 2021/08/04 17:25:30 by kde-wint      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft_internals.h"
#include <stdlib.h>

static char				*stringify(t_argprops *props, unsigned long long ull)
{
	char				*str;

	if (props->convtype == CONV_CHAR_UOCT || props->convtype ==
		CONV_SHORT_UOCT || props->convtype == CONV_UOCT || props->convtype ==
		CONV_LONG_UOCT || props->convtype == CONV_LONGLONG_UOCT)
		str = ft_ulltoa_base(ull, 8);
	else if (props->convtype == CONV_CHAR_UHEX_LWRCASE || props->convtype ==
		CONV_SHORT_UHEX_LWRCASE || props->convtype == CONV_UHEX_LWRCASE ||
		props->convtype == CONV_LONG_UHEX_LWRCASE || props->convtype ==
		CONV_LONGLONG_UHEX_LWRCASE)
		str = ft_ulltoa_base(ull, 16);
	else if (props->convtype == CONV_CHAR_UHEX_UPRCASE || props->convtype ==
		CONV_SHORT_UHEX_UPRCASE || props->convtype == CONV_UHEX_UPRCASE ||
		props->convtype == CONV_LONG_UHEX_UPRCASE || props->convtype ==
		CONV_LONGLONG_UHEX_UPRCASE)
	{
		str = ft_ulltoa_base(ull, 16);
		ft_strreplace(&str, ft_strtoupper(str));
	}
	else
		str = ft_ulltoa_base(ull, 10);
	return (str);
}

static long long		get_va_arg(t_argprops *props, va_list v)
{
	if (props->convtype == CONV_CHAR_UINT || props->convtype == CONV_CHAR_UOCT
		|| props->convtype == CONV_CHAR_UHEX_LWRCASE || props->convtype ==
		CONV_CHAR_UHEX_UPRCASE)
		return ((unsigned long long)(unsigned char)va_arg(v, unsigned int));
	if (props->convtype == CONV_SHORT_UINT || props->convtype == CONV_SHORT_UOCT
		|| props->convtype == CONV_SHORT_UHEX_LWRCASE || props->convtype ==
		CONV_SHORT_UHEX_UPRCASE)
		return ((unsigned long long)(unsigned short)va_arg(v, unsigned int));
	if (props->convtype == CONV_UINT || props->convtype == CONV_UOCT ||
		props->convtype == CONV_UHEX_LWRCASE || props->convtype ==
		CONV_UHEX_UPRCASE)
		return ((unsigned long long)va_arg(v, unsigned int));
	if (props->convtype == CONV_LONG_UINT || props->convtype == CONV_LONG_UOCT
		|| props->convtype == CONV_LONG_UHEX_LWRCASE || props->convtype ==
		CONV_LONG_UHEX_UPRCASE)
		return ((unsigned long long)va_arg(v, unsigned long));
	else
		return (va_arg(v, unsigned long long));
}

void					print_uint(
	t_argprops *props, va_list args, t_writer *writer)
{
	unsigned long long	ull;
	char				*str;
	int					written_loc;

	ull = get_va_arg(props, args);
	if (ull == (unsigned long long)0 && props->flags & FLAG_PRECIS &&
		props->precision == 0)
		str = ft_strdup("");
	else
		str = stringify(props, ull);
	while ((props->flags & FLAG_PRECIS && (int)ft_strlen(str) <
		props->precision) || (props->flags & FLAG_HT && *str != '0' &&
		(props->convtype == CONV_CHAR_UOCT || props->convtype == CONV_SHORT_UOCT
		|| props->convtype == CONV_UOCT || props->convtype == CONV_LONG_UOCT ||
		props->convtype == CONV_LONGLONG_UOCT)))
		ft_strreplace(&str, ft_strjoin("0", str));
	written_loc = ft_strlen(str);
	if (props->flags & FLAG_HT || props->flags & FLAG_MINFW)
		print_uint_prefix(props, &written_loc, ull);
	putnstr_w(writer, str, ft_strlen(str));
	ft_strdel(&str);
	if (props->flags & FLAG_MINFW && props->flags & FLAG_MINUS)
		uint_minfw_padder(props, &written_loc);
}
