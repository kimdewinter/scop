/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_get_next_line.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: kde-wint <kde-wint@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/04/22 15:49:31 by kde-wint      #+#    #+#                 */
/*   Updated: 2021/08/04 17:25:30 by kde-wint      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft_internals.h"

static int	multi_handler(char **line, char **permbuf)
{
	if (*permbuf == NULL)
	{
		*permbuf = ft_strnew(0);
		if (*permbuf == NULL)
			return (-1);
		else
			return (2);
	}
	if (*permbuf[0] == '\n')
	{
		*line = ft_strnew(0);
		ft_strreplace(permbuf, ft_strdup(*permbuf + 1));
		return (1);
	}
	*line = ft_strndup(*permbuf, ft_strchr(*permbuf, '\n') - *permbuf);
	ft_strreplace(permbuf, ft_strdup(ft_strchr(*permbuf, '\n') + 1));
	return (1);
}

static int	eof_handler(char **line, char **permbuf, int callcode)
{
	if (callcode == 0)
	{
		*line = NULL;
		ft_strdel(permbuf);
		return (0);
	}
	if (*permbuf[0] == '\n')
	{
		*line = ft_strnew(0);
		ft_strreplace(permbuf, ft_strdup(*permbuf + 1));
	}
	else if (ft_strchr(*permbuf, '\n') == NULL ||
			*(ft_strchr(*permbuf, '\n') + 1) == '\0')
	{
		*line = ft_strdup(*permbuf);
		ft_strreplace(permbuf, ft_strnew(0));
	}
	else
	{
		*line = ft_strndup(*permbuf, ft_strchr(*permbuf, '\n') - *permbuf);
		ft_strreplace(permbuf, ft_strdup(ft_strchr(*permbuf, '\n') + 1));
	}
	return (1);
}

int			ft_get_next_line(const int fd, char **line)
{
	static char			*permbuf[12000];
	char				buf[BUFF_SIZE + 1];

	if (read(fd, &buf, 0) < 0 || !line)
		return (-1);
	if (permbuf[fd] == NULL)
		if (multi_handler(line, &permbuf[fd]) != 2)
			return (-1);
	ft_bzero(buf, BUFF_SIZE + 1);
	if (ft_strchr(permbuf[fd], '\n') != ft_strrchr(permbuf[fd], '\n'))
		return (multi_handler(line, &permbuf[fd]));
	while (read(fd, &buf, BUFF_SIZE))
	{
		ft_strreplace(&permbuf[fd], ft_strjoin(permbuf[fd], buf));
		ft_bzero(buf, BUFF_SIZE + 1);
		if (ft_strchr(permbuf[fd], '\n') != NULL)
			return (multi_handler(line, &permbuf[fd]));
	}
	if (!read(fd, &buf, BUFF_SIZE) && *permbuf[fd] != '\0')
		return (eof_handler(line, &permbuf[fd], 1));
	if (*buf == '\0' && *permbuf[fd] == '\0')
		return (eof_handler(line, &permbuf[fd], 0));
	return (-1);
}
