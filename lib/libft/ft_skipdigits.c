/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_skipdigits.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: kde-wint <kde-wint@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/06 13:39:55 by kde-wint      #+#    #+#                 */
/*   Updated: 2021/11/08 18:24:03 by kde-wint      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "include/libft_internals.h"

void	ft_skipdigits(char **str)
{
	while (ft_isdigit(**str))
		(*str)++;
}
