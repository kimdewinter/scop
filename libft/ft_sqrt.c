/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_sqrt.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: kde-wint <kde-wint@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/06/09 12:52:27 by kde-wint      #+#    #+#                 */
/*   Updated: 2021/08/04 17:25:30 by kde-wint      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft_internals.h"

double	ft_sqrt(double x)
{
	float	temp;
	float	sqt;

	sqt = x / 2;
	temp = 0;
	while (sqt != temp)
	{
		temp = sqt;
		sqt = (x / temp + temp) / 2;
	}
	return (sqt);
}
