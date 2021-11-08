/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_skipchars.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: kde-wint <kde-wint@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/23 11:30:07 by kde-wint      #+#    #+#                 */
/*   Updated: 2021/11/08 18:24:03 by kde-wint      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "include/libft_internals.h"

void	ft_skipchars(char **str)
{
	while (ft_isalpha(**str))
		(*str)++;
}
