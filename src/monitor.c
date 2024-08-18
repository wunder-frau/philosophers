#include "philo.h"

/**
 * Checks if the philosopher has died.
 *
 * This function retrieves the philosopher's last meal time and compares it
 * to the current time to determine if the philosopher has exceeded their
 * allotted time to die. If the philosopher has died, the game over flag is
 * set, and the function returns true. Otherwise, it returns false.
 *
 * @param philo Pointer to the philosopher's data structure.
 * @return true if the philosopher has died, otherwise false.
 */
static bool	is_dead(t_philo *philo)
{
	long	last_meal_time;

	last_meal_time = philo->last_meal_time;
	if (last_meal_time == 0)
		last_meal_time = philo->table->init_time;
	if (get_cur_time() >= last_meal_time + philo->table->die)
	{
		printf("%ld\t%ld\t%s", get_cur_time() - philo->table->init_time,
			philo->id + 1, "has died\n");
		philo->table->game_over = 1;
		return (true);
	}
	return (false);
}

/**
 * Checks if the simulation should end due to all philosophers
 * being satiated or a philosopher's death.
 *
 * This function locks the mutex to ensure safe access to the
 * shared game state data. It first checks if all philosophers
 * have reached their required meal count. If true, the function
 * sets the `game_over` flag, unlocks the mutex, and returns 1,
 * indicating the game is over. If not all philosophers are satiated,
 * the function proceeds to check if any philosopher has died
 * using the `is_dead` function. The mutex is then unlocked, and the
 * function returns the current state of the `game_over` flag.
 *
 * @param philo Pointer to the philosopher's data structure.
 * @return 1 if the game is over due to satiation or death, otherwise 0.
 */
static int	is_game_over(t_philo *philo)
{
	pthread_mutex_lock(philo->table->mtx_act);
	if (philo->table->satiation_count == philo->table->size)
	{
		philo->table->game_over = 1;
		pthread_mutex_unlock(philo->table->mtx_act);
		return (1);
	}
	is_dead(philo);
	pthread_mutex_unlock(philo->table->mtx_act);
	return (philo->table->game_over);
}

void	*monitoring(void *table_ptr)
{
	t_table	*table;
	size_t	i;

	table = (t_table *)table_ptr;
	if (atomic_get(table->mtx_act, &table->init_time) == -1)
		return (NULL);
	ft_usleep(30, table);
	while (true)
	{
		i = 0;
		while (i < table->size)
		{
			if (is_game_over(&table->philosophers[i++]))
				return (NULL);
		}
	}
	return (NULL);
}
