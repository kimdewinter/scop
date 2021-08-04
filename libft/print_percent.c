/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   print_percent.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: kde-wint <kde-wint@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/25 13:53:29 by kde-wint      #+#    #+#                 */
/*   Updated: 2021/08/04 17:25:30 by kde-wint      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft_internals.h"

static void	minfw_padder(t_argprops *props, t_writer *writer)
{
	int		n;

	n = 1;
	while (n < props->minfw)
	{
		putnstr_w(writer, " ", 1);
		n++;
	}
}

void		print_percent(t_argprops *props, va_list args, t_writer *writer)
{
	(void)args;
	if (props->flags & FLAG_MINFW && !(props->flags & FLAG_MINUS))
		minfw_padder(props, writer);
	putnstr_w(writer, "%", 1);
	if (props->flags & FLAG_MINFW && props->flags & FLAG_MINUS)
		minfw_padder(props, writer);
}
