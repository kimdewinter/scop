/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   print_float_aux.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: kde-wint <kde-wint@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/09/18 15:53:19 by kde-wint      #+#    #+#                 */
/*   Updated: 2021/08/04 17:25:30 by kde-wint      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft_internals.h"
#include <stdlib.h>

static long double	get_va_arg(t_argprops *props, va_list args)
{
	if (props->convtype == CONV_FLOAT || props->convtype == CONV_DOUBLE)
		return (((long double)va_arg(args, double)));
	else
		return (va_arg(args, long double));
}

static void			fill_pre_separator(t_print_float_data *pfd)
{
	if (pfd->f >= 0.0L)
		pfd->pre_separator = ft_lltoa((unsigned long long)pfd->f);
	else
		pfd->pre_separator = ft_lltoa((unsigned long long)-pfd->f);
}

int					fill_pfd(
	t_argprops *props, va_list args, t_print_float_data *pfd)
{
	pfd->f = get_va_arg(props, args);
	if (NAN || POSINF || NEGINF)
		return (0);
	fill_pre_separator(pfd);
	fill_post_separator(props, pfd);
	pfd->pre_separator_len = ft_strlen(pfd->pre_separator);
	pfd->post_separator_len = ft_strlen(pfd->post_separator);
	return (1);
}
