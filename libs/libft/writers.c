/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   writers.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: kde-wint <kde-wint@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/12 17:13:41 by kde-wint      #+#    #+#                 */
/*   Updated: 2021/08/04 17:25:30 by kde-wint      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft_internals.h"

size_t		file_write(t_writer *self, const char *str, size_t len)
{
	(void)self;
	return (fwrite(str, 1, len, (FILE *)self->data));
}

size_t		out_write(t_writer *self, const char *str, size_t len)
{
	(void)self;
	return (write(1, str, len));
}

size_t		str_write(t_writer *self, const char *str, size_t len)
{
	size_t	steps;

	steps = 0;
	(void)self;
	while (steps < len)
	{
		*((t_sprintf_data *)self->data)->dst_walker = *str;
		((t_sprintf_data *)self->data)->dst_walker++;
		str++;
		steps++;
	}
	return (len);
}

void		putnstr_w(t_writer *writer, const char *str, size_t len)
{
	writer->written += writer->write(writer, str, len);
}
