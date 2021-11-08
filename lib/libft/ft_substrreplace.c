/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_substrreplace.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: kde-wint <kde-wint@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/19 17:00:05 by kde-wint      #+#    #+#                 */
/*   Updated: 2021/11/08 18:24:03 by kde-wint      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "include/libft_internals.h"

char	*replace_substring(const char *original,
							const char *start_replacing,
							const int length_to_replace,
							const char *replacement)
{
	char	*new;
	char	*pre_replace;
	char	*post_replace;

	pre_replace = ft_strndup(original, start_replacing - original);
	post_replace = ft_strdup(start_replacing + length_to_replace);
	new = ft_strjoin(pre_replace, (ft_strjoin(replacement, post_replace)));
	ft_strdel(&pre_replace);
	ft_strdel(&post_replace);
	return (new);
}
