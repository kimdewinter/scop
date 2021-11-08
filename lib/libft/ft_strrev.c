/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strrev.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: kde-wint <kde-wint@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/04/13 14:36:17 by kde-wint      #+#    #+#                 */
/*   Updated: 2021/11/08 18:24:03 by kde-wint      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "include/libft_internals.h"
#include <stdlib.h>

char	*ft_strrev(const char *s)
{
	char	*ret;
	int		i;

	i = ft_strlen(s) - 1;
	ret = ft_strnew(i + 1);
	if (!ret)
		return (NULL);
	while (i >= 0 && *s)
	{
		ret[i] = *s;
		s++;
		i--;
	}
	return (ret);
}
