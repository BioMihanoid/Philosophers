/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmilan <gmilan@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/29 18:56:49 by gmilan            #+#    #+#             */
/*   Updated: 2022/05/18 17:11:45 by gmilan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"Philosophers.h"

static int	ft_isspace(int c)
{
	if (c == ' ' || c == '\t' || c == '\n' || c == '\v'
		|| c == '\f' || c == '\r')
		return (1);
	else
		return (0);
}

static void	for_atoi(const char	*str, int *check_sign, size_t *i)
{
	while (ft_isspace(str[*i]))
		i++;
	if (str[*i] == '+' || str[*i] == '-')
		if (str[(*i)++] == '-')
			*check_sign = 1;
}

size_t	ft_strlen(const char *str)
{
	unsigned int	i;

	i = 0;
	while (*(str + i) != '\0')
		i++;
	return (i);
}

int	ft_atoi(const char *str)
{
	size_t				i;
	int					check_sign;
	unsigned long long	res;

	i = 0;
	check_sign = 0;
	res = 0;
	for_atoi(str, &check_sign, &i);
	if (ft_strlen(str) > 19 && check_sign)
		return (0);
	if (ft_strlen(str) > 19)
		return (-1);
	while (str[i] && str[i] >= '0' && str[i] <= '9')
	{
		res = res * 10 - (str[i] - '0');
		i++;
	}
	if (!check_sign)
		return (-res);
	else
		return (res);
}

long int	get_time(void)
{
	struct timeval	tv;
	long int		milliseconds;

	gettimeofday(&tv, NULL);
	milliseconds = tv.tv_sec * 1000 + tv.tv_usec / 1000;
	return (milliseconds);
}
