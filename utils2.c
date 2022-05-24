/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmilan <gmilan@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/08 17:03:32 by gmilan            #+#    #+#             */
/*   Updated: 2022/05/18 17:11:45 by gmilan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Philosophers.h"

void	ft_bzero(void *s, size_t n)
{
	unsigned char	*s_s;
	size_t			i;

	i = 0;
	s_s = (unsigned char *)s;
	while (i < n)
	{
		s_s[i] = '\0';
		i++;
	}
}

void	print_info(long int time, t_philo *philo, char *status)
{
	long int	t;

	pthread_mutex_lock(&philo->st_condition->print);
	t = philo->st_condition->start_meal;
	if (philo->st_condition->flag != 1)
		printf("%6ld %3d %s\n", time - t, philo->number, status);
	pthread_mutex_unlock(&philo->st_condition->print);
}

void	eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->st_condition->forks[philo->left_fork]);
	pthread_mutex_lock(&philo->st_condition->forks[philo->right_fork]);
	pthread_mutex_lock(&philo->mutex);
	philo->last_time_meals = get_time();
	pthread_mutex_unlock(&philo->mutex);
	print_info(get_time(), philo, "has taken a fork");
	print_info(get_time(), philo, "has taken a fork");
	print_info(get_time(), philo, "is eating");
	usleep(philo->st_condition->time_to_eat * 1000);
	pthread_mutex_unlock(&philo->st_condition->forks[philo->left_fork]);
	pthread_mutex_unlock(&philo->st_condition->forks[philo->right_fork]);
}

void	*life_one_philo(t_philo *philo)
{
	pthread_mutex_lock(&philo->st_condition->forks[philo->right_fork]);
	philo->last_time_meals = get_time();
	print_info(get_time(), philo, "has taken a fork");
	pthread_mutex_unlock(&philo->st_condition->forks[philo->right_fork]);
	print_info(get_time(), philo, "died");
	philo->st_condition->flag = 1;
	return (0);
}

int	ft_error(int key)
{
	printf("Error! ");
	if (key == 0)
		printf("The number of philosophers must be at least 1!\n");
	else if (key == 1)
		printf ("Less than 5 or more than 6 arguments were received!\n");
	else if (key == 2)
		printf ("Malloc has not allocated memory!\n");
	return (0);
}
