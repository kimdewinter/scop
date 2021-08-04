/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strncat.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: kde-wint <kde-wint@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/03/28 12:48:14 by kde-wint      #+#    #+#                 */
/*   Updated: 2021/08/04 17:25:30 by kde-wint      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft_internals.h"

char	*ft_strncat(char *s1, const char *s2, size_t n)
{
	int	i;

	i = 0;
	while (s1[i])
		i++;
	while (*s2 && n > 0)
	{
		s1[i] = *(s2);
		i++;
		n--;
		s2++;
	}
	s1[i] = '\0';
	return (s1);
}
