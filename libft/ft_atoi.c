/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_atoi.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: kde-wint <kde-wint@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/03/28 09:50:35 by kde-wint      #+#    #+#                 */
/*   Updated: 2019/04/13 13:10:59 by kde-wint      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

static int	ft_atoi_negative(const char *str)
{
	int		ret;

	ret = 0;
	str++;
	while (*str >= '0' && *str <= '9')
	{
		ret = ret * 10 + *str - '0';
		str++;
	}
	return (-ret);
}

int			ft_atoi(const char *str)
{
	int		ret;

	ret = 0;
	if ((*str == '+' && *(str + 1) >= '0' && *(str + 1) <= '9'))
		str++;
	else if ((*str == '-') &&
			*(str + 1) >= '0' && *(str + 1) <= '9')
		return (ft_atoi_negative(str));
	if (*str >= '0' && *str <= '9')
		while (*str >= '0' && *str <= '9')
		{
			ret = ret * 10 + *str - '0';
			str++;
		}
	else if (*str == '\t' || *str == '\n' || *str == '\v' ||
			*str == '\f' || *str == '\r' || *str == ' ')
		return (ft_atoi(str + 1));
	return (ret);
}
