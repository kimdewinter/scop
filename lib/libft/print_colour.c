/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   print_colour.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: kde-wint <kde-wint@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/21 14:59:49 by kde-wint      #+#    #+#                 */
/*   Updated: 2021/11/08 18:24:03 by kde-wint      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "include/libft_internals.h"

static const t_colour	g_colours[9] = {
	{"COLOUR_RESET", 12, "COLOR_RESET", 11, "\x1b[0m", 4},
	{"COLOUR_BLACK", 12, "COLOR_BLACK", 11, "\x1b[30m", 5},
	{"COLOUR_RED", 10, "COLOR_RED", 9, "\x1b[31m", 5},
	{"COLOUR_GREEN", 12, "COLOR_GREEN", 11, "\x1b[32m", 5},
	{"COLOUR_YELLOW", 13, "COLOR_YELLOW", 12, "\x1b[33m", 5},
	{"COLOUR_BLUE", 11, "COLOR_BLUE", 10, "\x1b[34m", 5},
	{"COLOUR_PURPLE", 13, "COLOR_PURPLE", 12, "\x1b[35m", 5},
	{"COLOUR_CYAN", 11, "COLOR_CYAN", 10, "\x1b[36m", 5},
	{"COLOUR_WHITE", 12, "COLOR_WHITE", 11, "\x1b[37m", 5}
};

static t_colour			*get_colour(const char *str, const int chars_remaining)
{
	size_t				i;
	int					uk_keylen;
	int					us_keylen;

	i = 0;
	while (i < sizeof(g_colours) / sizeof(t_colour))
	{
		uk_keylen = chars_remaining < (int)g_colours[i].uk_keylen ?
			chars_remaining : (int)g_colours[i].uk_keylen;
		us_keylen = chars_remaining < (int)g_colours[i].us_keylen ?
			chars_remaining : (int)g_colours[i].us_keylen;
		if (ft_strncmp(str, g_colours[i].uk_key, uk_keylen) == 0
			||
			ft_strncmp(str, g_colours[i].us_key, us_keylen) == 0)
			return ((t_colour *)&g_colours[i]);
		i++;
	}
	return (NULL);
}

static int				get_chars_to_skip(const char *str,
	const t_colour *colour_ptr)
{
	if (ft_strncmp(str, colour_ptr->uk_key, colour_ptr->uk_keylen) == 0)
		return (colour_ptr->uk_keylen);
	else if (ft_strncmp(str, colour_ptr->us_key, colour_ptr->us_keylen) == 0)
		return (colour_ptr->us_keylen);
	else
		return (0);
}

int						print_colour(char **str, t_writer *writer,
	const int chars_remaining)
{
	t_colour			*colour_ptr;

	colour_ptr = get_colour(*str, chars_remaining);
	if (colour_ptr == NULL)
		return (0);
	putnstr_w(writer, colour_ptr->value, colour_ptr->valuelen);
	*str += get_chars_to_skip(*str, colour_ptr);
	return (1);
}
