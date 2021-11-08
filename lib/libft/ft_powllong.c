/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_powllong.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: kde-wint <kde-wint@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/17 16:34:56 by kde-wint      #+#    #+#                 */
/*   Updated: 2021/11/08 18:24:03 by kde-wint      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "include/libft_internals.h"

static long long	expowner(const long long base, const long long exponent,
						const long long result)
{
	if (exponent > 1)
		return (expowner(base, exponent - 1, result * base));
	else
		return (result);
}

long long			ft_powllong(const long long base, const long long exponent)
{
	return (expowner(base, exponent, base));
}
