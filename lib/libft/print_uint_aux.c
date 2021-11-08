/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   print_uint_aux.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: kde-wint <kde-wint@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/08 15:12:07 by kde-wint      #+#    #+#                 */
/*   Updated: 2021/11/08 18:24:03 by kde-wint      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "include/libft_internals.h"

void				uint_minfw_padder(t_argprops *props, int *written)
{
	char			c;

	c = (props->flags & FLAG_ZERO && !(props->flags & FLAG_MINUS) &&
		!(props->flags & FLAG_PRECIS && *written <= props->precision)) ?
			'0' : ' ';
	if (c == '0' && props->flags & FLAG_ZERO && props->flags & FLAG_PRECIS &&
		*written >= props->precision)
		c = ' ';
	while (*written < props->minfw)
	{
		putnstr_w(props->writer, &c, 1);
		(*written)++;
	}
}

static void			hashtag(t_argprops *props)
{
	if (props->convtype == CONV_CHAR_UHEX_LWRCASE || props->convtype ==
		CONV_SHORT_UHEX_LWRCASE || props->convtype == CONV_UHEX_LWRCASE ||
		props->convtype == CONV_LONG_UHEX_LWRCASE || props->convtype ==
		CONV_LONGLONG_UHEX_LWRCASE)
		putnstr_w(props->writer, "0x", 2);
	else if (props->convtype == CONV_CHAR_UHEX_UPRCASE || props->convtype ==
			CONV_SHORT_UHEX_UPRCASE || props->convtype == CONV_UHEX_UPRCASE ||
			props->convtype == CONV_LONG_UHEX_UPRCASE || props->convtype ==
			CONV_LONGLONG_UHEX_UPRCASE)
		putnstr_w(props->writer, "0X", 2);
}

void				print_uint_prefix(t_argprops *props, int *written,
	unsigned long long ull)
{
	if (props->flags & FLAG_HT && ull != (unsigned long long)0 &&
		!(props->convtype == CONV_CHAR_UOCT || props->convtype ==
		CONV_SHORT_UOCT || props->convtype == CONV_UOCT || props->convtype ==
		CONV_LONG_UOCT || props->convtype == CONV_LONGLONG_UOCT))
	{
		*written += 2;
		if (props->flags & FLAG_MINFW && !(props->flags & FLAG_MINUS))
		{
			if (props->flags & FLAG_ZERO && !(props->flags & FLAG_PRECIS &&
				*written >= props->precision))
			{
				hashtag(props);
				uint_minfw_padder(props, written);
			}
			else
			{
				uint_minfw_padder(props, written);
				hashtag(props);
			}
		}
		else
			hashtag(props);
	}
	else if (!(props->flags & FLAG_MINUS))
		uint_minfw_padder(props, written);
}
