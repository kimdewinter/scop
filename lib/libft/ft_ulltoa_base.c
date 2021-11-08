/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_ulltoa_base.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: kde-wint <kde-wint@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/14 12:51:41 by kde-wint      #+#    #+#                 */
/*   Updated: 2021/11/08 18:24:03 by kde-wint      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "include/libft_internals.h"
#include "limits.h"

static char				get_char(const unsigned long long l)
{
	if (l < 10)
		return (l + '0');
	else
		return (l - 10 + 'a');
}

static int				digit_counter(const unsigned long long l,
	const unsigned int base, const unsigned int digits)
{
	if (l >= base)
		return (digit_counter(l / base, base, digits + 1));
	else
		return (digits + 1);
}

static void				get_str(char *str, const unsigned long long l,
	const unsigned int base, const unsigned int digits)
{
	if (l)
	{
		str[digits] = get_char(l % base);
		return (get_str(str, l / base, base, digits - 1));
	}
}

char					*ft_ulltoa_base(
	const unsigned long long l, const unsigned int base)
{
	unsigned int		digits;
	char				*str;

	if (l == 0)
		return (ft_strdup("0"));
	digits = digit_counter(l, base, 0);
	str = ft_strnew(digits);
	if (str == NULL)
		return (NULL);
	get_str(str, l, base, digits - 1);
	return (str);
}
