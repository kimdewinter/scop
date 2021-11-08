/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strlcat.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: kde-wint <kde-wint@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/03/30 17:47:21 by kde-wint      #+#    #+#                 */
/*   Updated: 2021/11/08 18:24:03 by kde-wint      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "include/libft_internals.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	dstlen;
	size_t	dstterminated;

	i = 0;
	dstlen = ft_strlen(dst);
	if (size == 0)
		return (ft_strlen(src));
	if (dstlen > size)
		dstterminated = dst[size] != 0;
	else
		dstterminated = dst[dstlen] != 0;
	while (dstlen + i + 1 < size && src[i])
	{
		dst[dstlen + i] = src[i];
		i++;
	}
	dst[dstlen + i] = '\0';
	if (dstterminated)
		return (ft_strlen(src) + size);
	else
		return (ft_strlen(src) + dstlen);
}
