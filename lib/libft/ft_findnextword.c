/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_findnextword.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: kde-wint <kde-wint@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/12/20 17:53:39 by kde-wint       #+#    #+#                */
/*   Updated: 2019/12/23 14:54:38 by kde-wint      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

char	*ft_findnextword(const char *str, const int spaces_to_skip)
{
	while (*str && *str != ' ')
		str++;
	if (*str == '\0')
		return (NULL);
	if (spaces_to_skip > 1)
		return (ft_findnextword(str + 1, spaces_to_skip - 1));
	return ((char *)str + 1);
}
