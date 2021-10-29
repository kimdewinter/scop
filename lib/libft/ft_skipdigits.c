/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_skipdigits.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: kde-wint <kde-wint@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/06 13:39:55 by kde-wint      #+#    #+#                 */
/*   Updated: 2021/08/04 17:25:30 by kde-wint      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft_internals.h"

void	ft_skipdigits(char **str)
{
	while (ft_isdigit(**str))
		(*str)++;
}
