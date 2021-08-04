/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strsplit.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: kde-wint <kde-wint@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/04/04 10:05:51 by kde-wint      #+#    #+#                 */
/*   Updated: 2021/08/04 17:25:30 by kde-wint      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft_internals.h"
#include <stdlib.h>

static int	lettercounter(const char *s, char c)
{
	int	lettercount;

	lettercount = 0;
	while (*s && *s != c)
	{
		lettercount++;
		s++;
	}
	return (lettercount);
}

static int	wordcounter(const char *s, char c)
{
	int	wordcount;

	wordcount = 0;
	if (*s != c && *s)
	{
		wordcount++;
		s++;
	}
	while (*s)
	{
		if (*s != c && *(s - 1) == c)
			wordcount++;
		s++;
	}
	return (wordcount);
}

static char	*wordfiller(char const *s, char c)
{
	char	*str;
	int		i;

	str = ft_strnew(lettercounter(s, c));
	i = 0;
	if (str == NULL)
		return (NULL);
	while (*s && *s != c)
	{
		str[i] = *s;
		i++;
		s++;
	}
	return (str);
}

char		**ft_strsplit(char const *s, char c)
{
	char	**uberstr;
	int		i;

	uberstr = (char **)ft_memalloc(sizeof(char *) * (wordcounter(s, c) + 1));
	i = 0;
	if (uberstr == NULL)
		return (NULL);
	if (!*s)
		return (uberstr);
	if (*s != c)
	{
		uberstr[i] = wordfiller(s, c);
		i++;
		s++;
	}
	while (*s)
	{
		if (*s != c && *(s - 1) == c)
		{
			uberstr[i] = wordfiller(s, c);
			i++;
		}
		s++;
	}
	return (uberstr);
}
