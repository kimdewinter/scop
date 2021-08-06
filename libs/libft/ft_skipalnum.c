/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_skipalnum.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: kde-wint <kde-wint@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/23 12:06:42 by kde-wint      #+#    #+#                 */
/*   Updated: 2021/08/04 17:25:30 by kde-wint      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft_internals.h"

void	ft_skipalnum(char **str)
{
	while (ft_isalnum(**str))
		(*str)++;
}
