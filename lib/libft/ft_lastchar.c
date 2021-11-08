/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_lastchar.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: kde-wint <kde-wint@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/09/18 18:20:35 by kde-wint      #+#    #+#                 */
/*   Updated: 2021/11/08 18:24:03 by kde-wint      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "include/libft_internals.h"

char	*ft_lastchar(char *str)
{
	return (str + ft_strlen(str) - 1);
}
