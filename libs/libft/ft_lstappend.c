/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_lstappend.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: kde-wint <kde-wint@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/04/08 18:29:51 by kde-wint      #+#    #+#                 */
/*   Updated: 2021/08/04 17:25:30 by kde-wint      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft_internals.h"
#include <stdlib.h>

void	ft_lstappend(t_list *lst)
{
	t_list *tmp;

	tmp = malloc(sizeof(t_list));
	tmp->content = NULL;
	tmp->content_size = 0;
	lst->next = tmp;
}
