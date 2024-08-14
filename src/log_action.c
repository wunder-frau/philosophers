#include "philo.h"

/**
 * Log a philosopher's action with a timestamp.
 */

bool	log_action(t_philo *philo, long timestamp, char *act_msg)
{
	t_table	*table;

	table = philo->table;
	pthread_mutex_lock(table->mtx_act);
	if (table->game_over == 0)
	{
		printf("%zu\t%zu\t%s", timestamp - table->init_time, philo->id + 1, act_msg);
		pthread_mutex_unlock(table->mtx_act);
		return (false);
	}
	pthread_mutex_unlock(table->mtx_act);
	return (true);
}