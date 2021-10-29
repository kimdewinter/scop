/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   print_float.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: kde-wint <kde-wint@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/09/06 17:31:17 by kde-wint      #+#    #+#                 */
/*   Updated: 2021/08/04 17:25:30 by kde-wint      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft_internals.h"
#include <stdlib.h>

static void	format_separator(t_argprops *props, t_print_float_data *pfd)
{
	if (props->flags & FLAG_HT || (props->precision > 0 &&
		!NAN && !POSINF && !NEGINF))
		pfd->separator = ft_strdup(".");
	else
		pfd->separator = ft_strnew(0);
	pfd->separator_len = ft_strlen(pfd->separator);
}

static void	format_prefix(t_argprops *props, t_print_float_data *pfd)
{
	int		len;
	int		i;

	if (props->flags & FLAG_MINFW &&
		!(props->flags & FLAG_MINUS))
		len = props->minfw - (pfd->pre_separator_len +
			pfd->separator_len + pfd->post_separator_len);
	else
		len = (pfd->f < (long double)0 || props->flags & FLAG_PLUS ||
			props->flags & FLAG_SPACE || pfd->f == -0.0) ? 1 : 0;
	pfd->prefix = ft_strnew(len);
	i = 0;
	while (props->flags & FLAG_MINFW && !(props->flags & FLAG_MINUS) && i < len)
	{
		pfd->prefix[i] = props->flags & FLAG_ZERO && !NEGINF ? '0' : ' ';
		i++;
	}
	i = props->flags & FLAG_ZERO && !NEGINF ? 0 : len - 1;
	if (pfd->f < (long double)0)
		pfd->prefix[i] = '-';
	else if (props->flags & FLAG_PLUS)
		pfd->prefix[i] = '+';
	else if (props->flags & FLAG_SPACE)
		pfd->prefix[i] = ' ';
	pfd->prefix_len = ft_strlen(pfd->prefix);
}

static void	format_postfix(t_argprops *props, t_print_float_data *pfd)
{
	int		len;
	int		i;

	len = props->minfw - (pfd->prefix_len + pfd->pre_separator_len +
		pfd->separator_len + pfd->post_separator_len);
	if (len > 0)
	{
		pfd->postfix = ft_strnew(len);
		i = 0;
		while (i < len)
		{
			pfd->postfix[i] = ' ';
			i++;
		}
	}
	else
		pfd->postfix = ft_strnew(0);
	pfd->postfix_len = ft_strlen(pfd->postfix);
}

static void	handle_specialcase(t_print_float_data *pfd)
{
	pfd->post_separator = ft_strnew(0);
	pfd->post_separator_len = 0;
	if (NAN)
		pfd->pre_separator = ft_strdup("nan");
	else if (POSINF || NEGINF)
		pfd->pre_separator = ft_strdup("inf");
	pfd->pre_separator_len = ft_strlen(pfd->pre_separator);
}

void		print_float(t_argprops *props, va_list args, t_writer *writer)
{
	t_print_float_data	pfd;
	char				*output;

	if (!(props->flags & FLAG_PRECIS))
		props->precision = 6;
	if (fill_pfd(props, args, &pfd) == 0)
		handle_specialcase(&pfd);
	format_separator(props, &pfd);
	format_prefix(props, &pfd);
	format_postfix(props, &pfd);
	output = ft_strjoin(pfd.prefix, ft_strjoin(
		pfd.pre_separator, ft_strjoin(
			pfd.separator, ft_strjoin(
				pfd.post_separator, pfd.postfix))));
	putnstr_w(writer, output, ft_strlen(output));
	free(pfd.prefix);
	free(pfd.pre_separator);
	free(pfd.separator);
	free(pfd.post_separator);
	free(pfd.postfix);
	free(output);
}
