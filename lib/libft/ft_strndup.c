/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strndup.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: kde-wint <kde-wint@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/03/28 11:11:18 by kde-wint      #+#    #+#                 */
/*   Updated: 2021/11/08 18:24:03 by kde-wint      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "include/libft_internals.h"
#include <stdlib.h>

char	*ft_strndup(const char *s1, size_t len)
{
	char	*s2;
	int		i;

	s2 = (char *)malloc(sizeof(char) * (len + 1));
	if (s2 == NULL)
		return (NULL);
	i = 0;
	while (s1[i] && len > 0)
	{
		s2[i] = s1[i];
		i++;
		len--;
	}
	s2[i] = '\0';
	return (s2);
}
