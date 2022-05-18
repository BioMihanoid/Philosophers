/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmilan <gmilan@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 10:50:31 by gmilan            #+#    #+#             */
/*   Updated: 2022/05/18 17:11:45 by gmilan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Philosophers.h"

void	*additional_function(t_condition **condition)
{
	print_info(get_time(), (*condition)->philo, "died");
	(*condition)->flag = 1;
	return (NULL);
}

void	*died(void *cond)
{
	int			i;
	t_condition	*condition;

	condition = cond;
	i = -1;
	while (++i < condition->number_of_philosophers)
	{
		if (get_time() - condition->philo[i].last_time_meals
			> condition->time_to_die)
			return (additional_function(&condition));
		if (condition->philo[i].count_meals == condition->optional_arg
			&& condition->optional_arg > 0)
			condition->ate_meal++;
		if (condition->ate_meal == condition->number_of_philosophers)
		{
			condition->flag = 1;
			return (0);
		}
		if (i + 1 == condition->number_of_philosophers)
			i = -1;
		usleep(1600);
	}
	return (NULL);
}
