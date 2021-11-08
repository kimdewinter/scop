/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_memcmp.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: kde-wint <kde-wint@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/03/25 16:24:21 by kde-wint      #+#    #+#                 */
/*   Updated: 2021/11/08 18:24:03 by kde-wint      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "include/libft_internals.h"

int		ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char	*ucs1;
	unsigned char	*ucs2;

	ucs1 = (unsigned char*)s1;
	ucs2 = (unsigned char*)s2;
	while (*ucs1 == *ucs2 && n > 1)
	{
		ucs1++;
		ucs2++;
		n--;
	}
	if (n == 0)
		return ((int)(*(ucs1 - 1) - *(ucs2 - 1)));
	return ((int)(*ucs1 - *ucs2));
}
