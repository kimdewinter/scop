/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_lookup.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: kde-wint <kde-wint@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/06 14:24:03 by kde-wint      #+#    #+#                 */
/*   Updated: 2021/11/08 18:24:03 by kde-wint      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "include/libft_internals.h"

int			ft_lookup(char c, char *arr, size_t size)
{
	size_t	i;

	i = 0;
	while (i < size)
	{
		if (c == arr[i])
			return (1);
		i++;
	}
	return (0);
}
