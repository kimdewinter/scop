/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strrchr.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: kde-wint <kde-wint@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/03/28 15:19:18 by kde-wint      #+#    #+#                 */
/*   Updated: 2021/08/04 17:25:30 by kde-wint      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft_internals.h"

char	*ft_strrchr(const char *s, int c)
{
	const char	*anchor;

	anchor = s;
	while (*s)
		s++;
	if (!c)
		return ((char *)s);
	while (s > anchor)
	{
		s--;
		if (*(s) == (char)c)
			return ((char *)s);
	}
	return (NULL);
}
