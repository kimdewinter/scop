/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   props_parser.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: kde-wint <kde-wint@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/08/13 19:01:44 by kde-wint      #+#    #+#                 */
/*   Updated: 2021/08/04 17:25:30 by kde-wint      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft_internals.h"

static const t_kvpair	g_conv_arr[43] = {
	{"b", CONV_BIN, 1},
	{"c", CONV_CHAR, 1},
	{"hhb", CONV_CHAR_BIN, 3},
	{"hhx", CONV_CHAR_UHEX_LWRCASE, 3},
	{"hhX", CONV_CHAR_UHEX_UPRCASE, 3},
	{"hhd", CONV_CHAR_INT, 3},
	{"hhi", CONV_CHAR_INT, 3},
	{"hhu", CONV_CHAR_UINT, 3},
	{"hho", CONV_CHAR_UOCT, 3},
	{"lf", CONV_DOUBLE, 2},
	{"f", CONV_FLOAT, 1},
	{"x", CONV_UHEX_LWRCASE, 1},
	{"X", CONV_UHEX_UPRCASE, 1},
	{"d", CONV_INT, 1},
	{"i", CONV_INT, 1},
	{"Lf", CONV_LONG_DOUBLE, 2},
	{"lb", CONV_LONG_BIN, 2},
	{"lx", CONV_LONG_UHEX_LWRCASE, 2},
	{"lX", CONV_LONG_UHEX_UPRCASE, 2},
	{"ld", CONV_LONG_INT, 2},
	{"li", CONV_LONG_INT, 2},
	{"lu", CONV_LONG_UINT, 2},
	{"lo", CONV_LONG_UOCT, 2},
	{"llb", CONV_LONGLONG_BIN, 3},
	{"llx", CONV_LONGLONG_UHEX_LWRCASE, 3},
	{"llX", CONV_LONGLONG_UHEX_UPRCASE, 3},
	{"lld", CONV_LONGLONG_INT, 3},
	{"lli", CONV_LONGLONG_INT, 3},
	{"llu", CONV_LONGLONG_UINT, 3},
	{"llo", CONV_LONGLONG_UOCT, 3},
	{"%", CONV_PERCENT, 1},
	{"p", CONV_PTR, 1},
	{"hb", CONV_SHORT_BIN, 2},
	{"hx", CONV_SHORT_UHEX_LWRCASE, 2},
	{"hX", CONV_SHORT_UHEX_UPRCASE, 2},
	{"hd", CONV_SHORT_INT, 2},
	{"hi", CONV_SHORT_INT, 2},
	{"hu", CONV_SHORT_UINT, 2},
	{"ho", CONV_SHORT_UOCT, 2},
	{"s", CONV_STRING, 1},
	{"S", CONV_STRING, 1},
	{"u", CONV_UINT, 1},
	{"o", CONV_UOCT, 1}
};

static const t_kvpair	g_flag_arr[5] = {
	{"-", FLAG_MINUS, 1},
	{"+", FLAG_PLUS, 1},
	{" ", FLAG_SPACE, 1},
	{"0", FLAG_ZERO, 1},
	{"#", FLAG_HT, 1},
};

static int				lookup(
	char *str, const t_kvpair *table, t_argprops *output, int *steps)
{
	size_t	i;

	i = 0;
	while (table == g_conv_arr && i < sizeof(g_conv_arr) / sizeof(t_kvpair))
	{
		if (ft_strncmp(str, table[i].key, table[i].keylen) == 0)
		{
			output->convtype = table[i].value;
			*steps = table[i].keylen;
			return (1);
		}
		i++;
	}
	while (table == g_flag_arr && i < sizeof(g_flag_arr) / sizeof(t_kvpair))
	{
		if (ft_strncmp(str, table[i].key, table[i].keylen) == 0)
		{
			output->flags |= table[i].value;
			*steps = table[i].keylen;
			return (1);
		}
		i++;
	}
	return (0);
}

static void				set_precision(char **str, t_argprops *props,
							va_list args)
{
	(*props).flags |= FLAG_PRECIS;
	(*str)++;
	if (**str == '*')
	{
		(*props).precision = va_arg(args, int);
		(*str)++;
	}
	else
	{
		(*props).precision = ft_isdigit(**str) ?
			ft_atoi(*str) : 0;
		ft_skipdigits(str);
	}
}

static void				set_minfw(char **str, t_argprops *props,
							va_list args)
{
	(*props).flags |= FLAG_MINFW;
	if (**str == '*')
	{
		(*props).minfw = va_arg(args, int);
		if ((*props).minfw <= 0)
		{
			(*props).minfw = -(*props).minfw;
			(*props).flags |= FLAG_MINUS;
		}
		(*str)++;
	}
	else
	{
		(*props).minfw = ft_atoi(*str);
		ft_skipdigits(str);
	}
}

static void				clean_props(t_argprops *props)
{
	(*props).flags = 0;
	(*props).minfw = 0;
	(*props).precision = 0;
	(*props).convtype = CONV_INVALID;
}

void					props_finder(char **str, t_argprops *props,
							int steps, va_list args)
{
	if (*(*str + 1) == '%')
	{
		putnstr_w(props->writer, *str, 1);
		*str += 2;
		return ;
	}
	*str += 1;
	clean_props(props);
	while ((*props).convtype == CONV_INVALID && **str != '\0')
	{
		if (lookup(*str, g_flag_arr, props, &steps))
			*str += steps;
		else if (**str == '.')
			set_precision(str, props, args);
		else if (ft_isdigit(**str) || **str == '*')
			set_minfw(str, props, args);
		else if (lookup(*str, g_conv_arr, props, &steps))
			*str += steps;
		else
		{
			ft_skipalnum(str);
			break ;
		}
	}
}
