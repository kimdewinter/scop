/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_printf.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: kde-wint <kde-wint@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/08/13 19:01:50 by kde-wint      #+#    #+#                 */
/*   Updated: 2021/08/04 17:25:30 by kde-wint      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft_internals.h"
#include <unistd.h>

static const t_print_fn	g_print_fn_arr[37] = {
	print_binary,
	print_char,
	print_binary,
	print_uint,
	print_uint,
	print_int,
	print_uint,
	print_uint,
	print_float,
	print_float,
	print_uint,
	print_uint,
	print_int,
	print_float,
	print_binary,
	print_uint,
	print_uint,
	print_int,
	print_uint,
	print_uint,
	print_binary,
	print_uint,
	print_uint,
	print_int,
	print_uint,
	print_uint,
	print_percent,
	print_ptr,
	print_binary,
	print_uint,
	print_uint,
	print_int,
	print_uint,
	print_uint,
	print_str,
	print_uint,
	print_uint
};

static void				set_writer(t_writer *writer, t_argprops *props)
{
	writer->write = out_write;
	writer->written = 0;
	props->writer = writer;
}

int						ft_printf(char *str, ...)
{
	va_list				args;
	t_argprops			props;
	t_writer			writer;

	va_start(args, str);
	set_writer(&writer, &props);
	while (*str != '\0')
	{
		if (*str == '%' && *(str + 1) != '%')
		{
			props_finder(&str, &props, 0, args);
			if (props.convtype != CONV_INVALID)
				g_print_fn_arr[props.convtype](&props, args, &writer);
			continue;
		}
		if (*str == 'C' && print_colour(&str, &writer, ft_strlen(str)))
			continue;
		if (*str == '%' && *(str + 1) == '%')
			str++;
		putnstr_w(&writer, str, 1);
		str++;
	}
	return (writer.written);
}
