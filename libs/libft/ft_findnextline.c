/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_findnextline.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: kde-wint <kde-wint@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/12/23 12:31:29 by kde-wint       #+#    #+#                */
/*   Updated: 2019/12/23 15:50:20 by kde-wint      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

char	*ft_findnextline(const char *str, const int linebreaks_to_skip)
{
	while (*str && *str != '\n')
		str++;
	if (*str == '\0')
		return (NULL);
	if (linebreaks_to_skip > 1)
		return (ft_findnextline(str + 1, linebreaks_to_skip - 1));
	return ((char *)str + 1);
}
