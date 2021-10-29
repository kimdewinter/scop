/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_lastchar.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: kde-wint <kde-wint@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/09/18 18:20:35 by kde-wint      #+#    #+#                 */
/*   Updated: 2021/08/04 17:25:30 by kde-wint      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft_internals.h"

char	*ft_lastchar(char *str)
{
	return (str + ft_strlen(str) - 1);
}
