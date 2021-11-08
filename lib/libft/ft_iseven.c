/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_iseven.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: kde-wint <kde-wint@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/09/15 18:21:12 by kde-wint      #+#    #+#                 */
/*   Updated: 2021/11/08 18:24:03 by kde-wint      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "include/libft_internals.h"

int		ft_iseven(long long n)
{
	if (n % 2 == 0)
		return (1);
	return (0);
}
