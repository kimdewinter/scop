/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_lltoa.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: kde-wint <kde-wint@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/06 14:23:13 by kde-wint      #+#    #+#                 */
/*   Updated: 2021/08/04 17:25:30 by kde-wint      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft_internals.h"
#include "stdlib.h"
#include "limits.h"

static int	negcheck(long long *n)
{
	if (*n < 0)
	{
		*n = -*(n);
		return (1);
	}
	return (0);
}

static int	deccheck(long long n, int neg)
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

static char	*edgecasehandler(long long n)
{
	if (n == 0)
		return (ft_strdup("0"));
	return (ft_strdup("-9223372036854775808"));
}

char		*ft_lltoa(long long n)
{
	int		decimator;
	char	*str;
	int		neg;

	if (n == 0 || n == LLONG_MIN)
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
