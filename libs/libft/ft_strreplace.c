/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strreplace.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: kde-wint <kde-wint@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/04/13 16:00:01 by kde-wint      #+#    #+#                 */
/*   Updated: 2019/04/13 17:29:29 by kde-wint      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

void	ft_strreplace(char **s, char *new)
{
	free(*s);
	*s = new;
}
