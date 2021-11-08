/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   print_ptr.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: kde-wint <kde-wint@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/14 11:25:55 by kde-wint      #+#    #+#                 */
/*   Updated: 2021/11/08 18:24:03 by kde-wint      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "include/libft_internals.h"

static void	minfw_padder(t_writer *writer, int padcounter)
{
	while (padcounter > 0)
	{
		putnstr_w(writer, " ", 1);
		padcounter--;
	}
}

void		print_ptr(t_argprops *props, va_list args, t_writer *writer)
{
	void	*ptr;
	char	*str;
	int		len;

	ptr = va_arg(args, void *);
	str = ft_ulltoa_base((long long)ptr, 16);
	ft_strreplace(&str, ft_strjoin("0x", str));
	len = ft_strlen(str);
	if (props->flags & FLAG_MINFW && !(props->flags & FLAG_MINUS))
		minfw_padder(writer, props->minfw - len);
	putnstr_w(writer, str, len);
	ft_strdel(&str);
	if (props->flags & FLAG_MINFW && props->flags & FLAG_MINUS)
		minfw_padder(writer, props->minfw - len);
}
