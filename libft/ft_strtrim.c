/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strtrim.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: kde-wint <kde-wint@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/04/04 09:17:58 by kde-wint      #+#    #+#                 */
/*   Updated: 2021/08/04 17:25:30 by kde-wint      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft_internals.h"
#include <stdlib.h>

char	*ft_strtrim(const char *s)
{
	int		i;
	int		revi;
	char	*ret;
	int		reti;

	i = 0;
	revi = ft_strlen(s) - 1;
	reti = 0;
	while (s[i] == ' ' || s[i] == '\n' || s[i] == '\t')
		i++;
	while ((s[revi] == ' ' || s[revi] == '\n' || s[revi] == '\t') && s[i])
		revi--;
	ret = (char *)malloc(sizeof(char) * (revi - i + 2));
	if (ret == NULL)
		return (NULL);
	if (!s[i])
		*ret = '\0';
	while (s[i] && i <= revi)
	{
		ret[reti] = s[i];
		reti++;
		i++;
	}
	ret[reti] = '\0';
	return (ret);
}
