#include "philo.h"

/**
 * Log a philosopher's action with a timestamp.
 */
void	log_action(t_philo *philo, const char *event_message)
{
	t_time	time;

	pthread_mutex_lock(&philo->locks->print);
	time = get_current_time() - philo->intervals.start;
	printf("%zu %zu %s\n", time, philo->id + 1, event_message);
	pthread_mutex_unlock(&philo->locks->print);
}