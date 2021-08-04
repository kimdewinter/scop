/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   print_float_roundoff.c                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: kde-wint <kde-wint@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/02 19:32:06 by kde-wint      #+#    #+#                 */
/*   Updated: 2021/08/04 17:25:30 by kde-wint      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft_internals.h"

static int			round_down(char c)
{
	if ((c + '0') % 2 == 0)
		return (1);
	return (0);
}

static void			one_up(int i, t_print_float_data *pfd, char *str)
{
	if (str[i] >= '0' && str[i] <= '8')
		str[i]++;
	else if (str[i] == '9')
	{
		str[i] = '0';
		if (i > 0)
			one_up(i - 1, pfd, str);
		else if (str == pfd->post_separator)
			one_up(ft_lastchari(pfd->pre_separator), pfd, pfd->pre_separator);
		else if (str == pfd->pre_separator)
			ft_strreplace(&(pfd->pre_separator),
				ft_strjoin("1", pfd->pre_separator));
	}
}

void				round_off(int i, t_print_float_data *pfd, char *str)
{
	if (str[i] >= '0' && str[i] <= '4')
		return ;
	if (str[i] == '5')
	{
		if (i > 0 && round_down(str[i - 1]))
			return ;
		if (i == 0 && round_down(*ft_lastchar(pfd->pre_separator)))
			return ;
	}
	if (i == 0)
		one_up(ft_lastchari(pfd->pre_separator), pfd, pfd->pre_separator);
	else
		one_up(i - 1, pfd, str);
}
