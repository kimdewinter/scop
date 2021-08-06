/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   print_str.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: kde-wint <kde-wint@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/04 12:57:27 by kde-wint      #+#    #+#                 */
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

void		print_str(t_argprops *props, va_list args, t_writer *writer)
{
	char	*str;
	int		len;

	str = va_arg(args, char *);
	if (str == NULL)
		str = ft_strdup("(null)");
	len = props->flags & FLAG_PRECIS && props->precision < (int)ft_strlen(str) ?
		props->precision : (int)ft_strlen(str);
	if (props->flags & FLAG_MINFW && !(props->flags & FLAG_MINUS))
		minfw_padder(props, len, writer);
	putnstr_w(writer, str, len);
	if (ft_strcmp(str, "(null)") == 0)
		ft_strdel(&str);
	if (props->flags & FLAG_MINFW && props->flags & FLAG_MINUS)
		minfw_padder(props, len, writer);
}
