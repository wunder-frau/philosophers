#include "philo.h"

bool	is_dead(t_philo *philo)
{
	t_time curr;

	curr = get_current_time();
	if (curr >= philo->last_meal_time + philo->intervals->die)
	{
		pthread_mutex_lock(&philo->locks->death);
		if (philo->action != DEAD)
		{
			philo->action = DEAD;
			log_action(philo, "has died");
		}
		pthread_mutex_unlock(&philo->locks->death);
		return (true);
	}
	return (false);
}

static bool is_any_dead(const t_table *table)
{
	size_t	i;

	i = 0;
	while (i < table->size)
	{
		if (table->philosophers[i].action == DEAD)
			return (true);
		++i;
	}
	return (false);
}

/**
 * Get the current time in milliseconds.
 */
t_time	get_current_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
	{
		perror("Error: gettimeofday");
		exit(EXIT_FAILURE);
	}
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
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
	pthread_mutex_destroy(&table->locks.death);
	if (table->forks != NULL)
	{
		//TODO: remove for loop 
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

void	*monitoring(void *table_ptr)
{
	t_table	*table;

	table = (t_table *)table_ptr;
	while (1)
	{
		if (is_any_dead(table))
			break ;
	}
	return (NULL);
}
