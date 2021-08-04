/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   print_char.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: kde-wint <kde-wint@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/08/17 14:23:34 by kde-wint      #+#    #+#                 */
/*   Updated: 2021/08/04 17:25:30 by kde-wint      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft_internals.h"

static void	minfw_padder(t_argprops *props, int n, t_writer *writer)
{
	while (n < props->minfw)
	{
		putnstr_w(writer, " ", 1);
		n++;
	}
}

void		print_char(t_argprops *props, va_list args, t_writer *writer)
{
	char	c;

	c = (char)va_arg(args, int);
	if (props->flags & FLAG_MINFW && !(props->flags & FLAG_MINUS))
		minfw_padder(props, 1, writer);
	putnstr_w(writer, &c, 1);
	if (props->flags & FLAG_MINFW && props->flags & FLAG_MINUS)
		minfw_padder(props, 1, writer);
}
