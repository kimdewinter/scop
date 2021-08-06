/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_itoa.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: kde-wint <kde-wint@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/03/30 12:54:48 by kde-wint      #+#    #+#                 */
/*   Updated: 2021/08/04 17:25:30 by kde-wint      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft_internals.h"
#include <stdlib.h>

static int	negcheck(int *n)
{
	if (*n < 0)
	{
		*n = -*(n);
		return (1);
	}
	return (0);
}

static int	deccheck(int n, int neg)
{
	int		decimator;

	decimator = 1;
	while (n > 9)
	{
		decimator++;
		n /= 10;
	}
	if (neg == 1)
		decimator++;
	return (decimator);
}

static char	*edgecasehandler(int n)
{
	if (n == 0)
		return (ft_strdup("0"));
	return (ft_strdup("-2147483648"));
}

char		*ft_itoa(int n)
{
	int		decimator;
	char	*str;
	int		neg;

	if (n == 0 || n == -2147483648)
		return (edgecasehandler(n));
	neg = negcheck(&n);
	decimator = deccheck(n, neg);
	str = (char *)malloc(sizeof(char) * (decimator + 1));
	if (str == NULL)
		return (NULL);
	str[decimator] = '\0';
	while (decimator)
	{
		decimator--;
		if (neg == 1 && decimator == 0)
		{
			str[decimator] = '-';
			return (str);
		}
		str[decimator] = (n % 10) + '0';
		n /= 10;
	}
	return (str);
}
