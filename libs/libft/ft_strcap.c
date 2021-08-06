/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strcap.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: kde-wint <kde-wint@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/04/13 16:25:16 by kde-wint      #+#    #+#                 */
/*   Updated: 2021/08/04 17:25:30 by kde-wint      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft_internals.h"

char				*ft_strcap(char *s)
{
	int i;
	int	first;

	i = 0;
	first = 1;
	while (s[i])
	{
		if (ft_isalnum(s[i]) && first)
		{
			s[i] = (char)ft_toupper(s[i]);
			first = 0;
		}
		if ((s[i] == '.' && s[i + 1] != '.') || (s[i] == '\n' &&
					(s[i + 1] != ' ' || s[i + 1] != '\t') && s[i + 2] != '-'))
			first = 1;
		i++;
	}
	return (s);
}
