#include "Philosophers.h"

void	*died(void *cond)
{
	int			i;
	t_condition	*condition;

	condition = cond;
	i = -1;
	while (++i < condition->number_of_philosophers)
	{
		printf ("\n%d\n", (get_time() - condition->philo[i].last_time_meals) >
						  condition->time_to_die);
		if ((get_time() - condition->philo[i].last_time_meals) >
		condition->time_to_die)
		{
			print_info(get_time(), condition->philo, "died");
			condition->flag = 1;
			return (NULL);
		}
		if (condition->philo[i].count_meals == condition->optional_arg && condition->optional_arg > 0)
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