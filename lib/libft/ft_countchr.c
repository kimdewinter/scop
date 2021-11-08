/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_countchr.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: kde-wint <kde-wint@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/03/02 16:44:14 by kde-wint      #+#    #+#                 */
/*   Updated: 2021/11/08 18:24:03 by kde-wint      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "include/libft_internals.h"

size_t	ft_countchr(const char *s, const int c)
{
	size_t	chr_counter;

	chr_counter = 0;
	while (*s || *s == (char)c)
	{
		if (*s == (char)c)
			chr_counter++;
		s++;
	}
	return (chr_counter);
}
