/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_ulltoa.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: kde-wint <kde-wint@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/09 12:52:49 by kde-wint      #+#    #+#                 */
/*   Updated: 2021/11/08 18:24:03 by kde-wint      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "include/libft_internals.h"
#include "stdlib.h"
#include "limits.h"

static int	deccheck(unsigned long long n)
{
	int		decimator;

	decimator = 1;
	while (n > 9)
	{
		decimator++;
		n /= 10;
	}
	return (decimator);
}

char		*ft_ulltoa(unsigned long long n)
{
	int		decimator;
	char	*str;

	decimator = deccheck(n);
	str = (char *)malloc(sizeof(char) * (decimator + 1));
	if (str == NULL)
		return (NULL);
	str[decimator] = '\0';
	while (decimator)
	{
		decimator--;
		str[decimator] = (n % 10) + '0';
		n /= 10;
	}
	return (str);
}
