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
	pthread_mutex_lock(&philo->st_condition->print);
	if (philo->st_condition->flag != 1)
		printf("%ld %d %s\n", time - philo->st_condition->start_meal,
			   philo->number, status);
	pthread_mutex_unlock(&philo->st_condition->print);
}

void	eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->st_condition->forks[philo->left_fork]);
	pthread_mutex_lock(&philo->st_condition->forks[philo->right_fork]);
	philo->last_time_meals = get_time();
	pthread_mutex_lock(&philo->st_condition->print);
	print_info(get_time(), philo, "has taken a fork");
	print_info(get_time(), philo, "has taken a fork");
	print_info(get_time(), philo, "is eating");
	pthread_mutex_unlock(&philo->st_condition->print);
	usleep(philo->st_condition->time_to_sleep * 1000);
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
