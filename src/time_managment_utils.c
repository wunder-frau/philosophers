#include "philo.h"

/**
 * Get the current time in milliseconds.
 */
long	get_current_time(void)
{
	struct timeval	curr_time;
	long			timestamp;

	gettimeofday(&curr_time, NULL);
	timestamp = curr_time.tv_sec * 1000 + curr_time.tv_usec / 1000;
	return (timestamp);
}

/**
 * Pauses execution for a specified duration while checking a termination condition.
 * 
 * The function records the start time, then repeatedly sleeps for 500 microseconds 
 * until the elapsed time reaches `msec` or until a termination condition (`game_over`) is met.
 *
 * @param msec Duration in milliseconds to pause.
 * @param table Pointer to a `t_table` structure containing the termination condition and mutex.
 */
void	ft_usleep(int msec, t_table *table)
{
	long	usleep_start;

	usleep_start = get_current_time();
	while (get_current_time() - usleep_start < msec
		&& atomic_get(table->mtx_act, &table->game_over) == 0)
		usleep(500);
}

/**
 * Calculates and adjusts the action gap time for philosophers.
 *
 * This function computes the time gap (wait time) between actions 
 * based on the time to die, eat, and sleep, ensuring that the gap 
 * time is non-negative.
 *
 */
int	calculate_action_gap(t_time die, t_time eat, t_time sleep)
{
	int action_gap;

	action_gap = (die - (eat + sleep)) / 2;
	if (action_gap < 0)
		action_gap = 0;
	return (action_gap);
}
