#include "philo.h"

bool	is_dead(t_philo *philo)
{
	unsigned long current_time;
	unsigned long time_since_last_meal;

	current_time = get_current_time();
	time_since_last_meal = current_time - philo->last_meal_time;
	if (philo->intervals.die == 0)
	{
		printf("Error: die interval is 0. This should be checked.\n");
		return (false);
	}
	if (time_since_last_meal >= philo->intervals.die)
	{
		pthread_mutex_lock(&philo->locks->dead);
		if (philo->action != DEAD)
		{
			philo->action = DEAD;
			log_action(philo, "has died");
		}
		pthread_mutex_unlock(&philo->locks->dead);
		return (true);
	}
	return (false);
}

/**
*	TODO:	Implement `create_threads()` to handle thread creation and
*			`join_threads()` to handle thread joining separately.
*			Move this functions to the `thread_management.c` file.
*/
void init(t_table *table)
{
	size_t	i;

	i = 0;
	while (i < table->size)
	{
		pthread_create(&table->philosophers[i].thread, NULL, &act, (void *)&table->philosophers[i]);
		/*{
			pthread_mutex_lock(&table->locks.print);
			printf("%zu", table->philosophers[i].id);
			pthread_mutex_unlock(&table->locks.print);
		}*/
		++i;
	}
	i = 0;
	while (i < table->size)
	{
		if (pthread_join(table->philosophers[i].thread, NULL))
			printf("Error: pthread_join failed\n");
		++i;
	}
}
