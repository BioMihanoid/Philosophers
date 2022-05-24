/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmilan <gmilan@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/23 13:11:26 by gmilan            #+#    #+#             */
/*   Updated: 2022/05/18 18:01:40 by gmilan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_philo		t_philo;

typedef struct s_condition
{
	int				number_of_philosophers;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	long int		start_meal;
	int				optional_arg;
	int				ate_meal;
	int				flag;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print;
	pthread_mutex_t	mutex;
	t_philo			*philo;
	pthread_t		life;
}	t_condition;

typedef struct s_philo
{
	int				number;
	int				right_fork;
	int				left_fork;
	int				count_meals;
	long int		last_time_meals;
	t_condition		*st_condition;
	pthread_mutex_t	mutex;
	pthread_t		thread;
}	t_philo;

int			ft_atoi(const char *str);
long int	get_time(void);
void		ft_bzero(void *s, size_t n);
void		eat(t_philo *philo);
void		*life_one_philo(t_philo *philo);
int			ft_error(int key);
void		*died(void *cond);
void		print_info(long int time, t_philo *philo, char *status);

#endif
