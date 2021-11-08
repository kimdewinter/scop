/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   print_float_post_separator.c                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: kde-wint <kde-wint@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/12/04 12:30:34 by kde-wint      #+#    #+#                 */
/*   Updated: 2021/11/08 18:24:03 by kde-wint      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "include/libft_internals.h"

static void			handle_zeroes_decimals(
	t_argprops *props, t_print_float_data *pfd)
{
	int				decimator;

	pfd->post_separator = ft_strnew(props->precision + 1);
	decimator = 0;
	while (decimator < props->precision)
	{
		pfd->post_separator[decimator] = '0';
		decimator++;
	}
}

static char			*longdouble_to_string(t_argprops *props,
	t_print_float_data *pfd)
{
	int				decimator;
	char			*str;

	decimator = 0;
	str = ft_strnew(0);
	while (decimator <= props->precision)
	{
		pfd->decimals *= 10;
		decimator++;
		if (decimator % 17 == 0)
		{
			ft_strreplace(&str, ft_strjoin(str, ft_lltoa(pfd->decimals)));
			pfd->decimals -= (unsigned long long)pfd->decimals;
		}
		if (pfd->decimals == (long double)0)
		{
			while (decimator <= props->precision)
			{
				ft_strreplace(&str, ft_strjoin(str, "0"));
				decimator++;
			}
		}
	}
	ft_strreplace(&str, ft_strjoin(str, ft_lltoa(pfd->decimals)));
	return (str);
}

void				fill_post_separator(
	t_argprops *props, t_print_float_data *pfd)
{
	if (pfd->f >= 0.0L)
		pfd->decimals = pfd->f - (long double)(unsigned long long)pfd->f;
	else
		pfd->decimals = -pfd->f - (long double)(unsigned long long)-pfd->f;
	if (pfd->decimals != 0.0L)
	{
		pfd->post_separator = longdouble_to_string(props, pfd);
		round_off(props->precision, pfd, pfd->post_separator);
		pfd->post_separator[props->precision] = '\0';
	}
	else
		handle_zeroes_decimals(props, pfd);
}
