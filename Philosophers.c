/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmilan <gmilan@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/23 13:11:16 by gmilan            #+#    #+#             */
/*   Updated: 2022/05/18 17:11:44 by gmilan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Philosophers.h"

void	init_philo(t_condition *condition)
{
	int	i;

	i = 0;
	while (i < condition->number_of_philosophers)
	{
		condition->philo[i].number = i + 1;
		condition->philo[i].left_fork = i;
		condition->philo[i].right_fork = i + 1;
		condition->philo[i].count_meals = 0;
		condition->philo[i].last_time_meals = get_time();
		condition->philo[i].st_condition = condition;
		if (i + 1 == condition->number_of_philosophers)
			condition->philo[i].right_fork = 0;
		pthread_mutex_init(&condition->forks[i], 0);
		i++;
	}
}

int	init_condition(t_condition *condition, int argc, char **argv)
{
	condition->number_of_philosophers = ft_atoi(argv[1]);
	if (condition->number_of_philosophers < 1)
		return (ft_error(0));
	condition->time_to_die = ft_atoi(argv[2]);
	condition->time_to_eat = ft_atoi(argv[3]);
	condition->time_to_sleep = ft_atoi(argv[4]);
	if (argc > 5)
		condition->optional_arg = ft_atoi(argv[5]);
	else
		condition->optional_arg = 0;
	condition->forks = NULL;
	condition->philo = malloc(sizeof(t_philo)
			* condition->number_of_philosophers);
	if (!condition->philo)
		return (ft_error(2));
	condition->forks = malloc(sizeof(pthread_mutex_t)
			* condition->number_of_philosophers);
	if (!condition->forks)
		return (ft_error(2));
	condition->ate_meal = 0;
	condition->flag = 0;
	ft_bzero(condition->philo, sizeof(t_philo));
	init_philo(condition);
	return (1);
}

void	*routine(void *ph)
{
	t_philo	*philo;

	philo = ph;
	if (philo->st_condition->number_of_philosophers == 1)
		return (life_one_philo(philo));
	if (philo->number % 2 == 0)
		usleep(1600);
	while (philo->st_condition->flag != 1)
	{
		eat(philo);
		print_info (get_time(), philo, "is sleeping");
		usleep(philo->st_condition->time_to_sleep * 1000);
		print_info(get_time(), philo, "is thinking");
		philo->count_meals++;
	}
	return (0);
}

void	create_philo(t_condition *condition)
{
	int	i;

	i = -1;
	while (++i < condition->number_of_philosophers)
		pthread_create(&condition->philo[i].thread, 0, &routine,
			&condition->philo[i]);
}

int	main(int argc, char **argv)
{
	t_condition	condition;
	int			i;

	i = -1;
	pthread_mutex_init(&condition.print, 0);
	if (argc < 5 || argc > 6)
		return (ft_error(1));
	condition.start_meal = get_time();
	if (!init_condition(&condition, argc, argv))
		return (0);
	create_philo(&condition);
	pthread_create(&condition.life, 0, &died, &condition);
	while (++i < condition.number_of_philosophers)
		pthread_join(condition.philo[i].thread, NULL);
	pthread_join(condition.life, 0);
	free(condition.philo);
	free(condition.forks);
	return (0);
}
