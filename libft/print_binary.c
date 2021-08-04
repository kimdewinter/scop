/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   print_binary.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: kde-wint <kde-wint@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/17 15:35:07 by kde-wint      #+#    #+#                 */
/*   Updated: 2021/08/04 17:25:30 by kde-wint      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft_internals.h"

static void			minfw_padder(const t_argprops *props, int n,
						t_writer *writer)
{
	while (n < props->minfw)
	{
		putnstr_w(writer, " ", 1);
		n++;
	}
}

static long long	get_va_arg(const t_argprops *props, va_list v)
{
	if (props->convtype == CONV_CHAR_BIN)
		return ((long long)(char)va_arg(v, int));
	if (props->convtype == CONV_SHORT_BIN)
		return ((long long)(short)va_arg(v, int));
	if (props->convtype == CONV_BIN)
		return ((long long)va_arg(v, int));
	if (props->convtype == CONV_LONG_BIN)
		return ((long long)va_arg(v, long));
	else
		return (va_arg(v, long long));
}

static int			get_bits(const t_argprops *props)
{
	if (props->convtype == CONV_CHAR_BIN)
		return (8);
	if (props->convtype == CONV_SHORT_BIN)
		return (16);
	if (props->convtype == CONV_BIN)
		return (32);
	return (64);
}

static void			print_bit(const long long ll, const int remaining_bits,
						const int ll_bits, t_argprops *props)
{
	if (remaining_bits == 0)
		return ;
	if (!((long long)1 << (remaining_bits - 1) & ll) ||
		(props->flags & FLAG_PRECIS && remaining_bits > ll_bits))
		putnstr_w(props->writer, "0", 1);
	else
		putnstr_w(props->writer, "1", 1);
	print_bit(ll, remaining_bits - 1, ll_bits, props);
}

void				print_binary(t_argprops *props, va_list args,
						t_writer *writer)
{
	long long		ll;
	int				ll_bits;
	int				total_bits;

	ll = get_va_arg(props, args);
	ll_bits = get_bits(props);
	total_bits = props->flags & FLAG_PRECIS && props->precision > ll_bits ?
		props->precision : ll_bits;
	if (props->flags & FLAG_MINFW && !(props->flags & FLAG_MINUS))
		minfw_padder(props, total_bits, writer);
	if (ll < 0)
	{
		putnstr_w(writer, "1", 1);
		ll = -ll;
	}
	else
		putnstr_w(writer, "0", 1);
	print_bit(ll, total_bits - 1, ll_bits, props);
	if (props->flags & FLAG_MINFW && props->flags & FLAG_MINUS)
		minfw_padder(props, total_bits, writer);
}
