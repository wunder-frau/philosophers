#include "philo.h"

/**
 * Get the current time in milliseconds.
 */
long	get_current_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
	{
		perror("Error: gettimeofday");
		exit(EXIT_FAILURE);
	}
	return ((long)time.tv_sec * 1000 + (long)time.tv_usec / 1000);
}

/*
* Safely sleep for a given duration,
* periodically checking if the philosopher has died.
*/
int ft_safe_usleep(t_time duration, t_philo *philo)
{
	t_time start_time = get_current_time();

	while ((get_current_time() - start_time) < duration)
	{
		if (is_dead(philo)) {
			return 1;
		}
		usleep(500);
	}
	return (0);
}

void destroy_and_free(t_table *table)
{
	pthread_mutex_destroy(&table->locks.eat);
	pthread_mutex_destroy(&table->locks.print);
	pthread_mutex_destroy(&table->locks.dead);
	if (table->forks != NULL)
	{
		//TO DO remove for loop 
		for (size_t i = 0; i < table->size; ++i)
		{
			pthread_mutex_destroy(&table->forks[i]);
		}
	}
	if (table->philosophers != NULL)
		free(table->philosophers);
	if (table->forks != NULL)
		free(table->forks);
}