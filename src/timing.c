/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   timing.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: istasheu <istasheu@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 02:14:50 by istasheu          #+#    #+#             */
/*   Updated: 2024/08/19 02:14:51 by istasheu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/**
 * Get the current time in milliseconds.
 */
long	get_curr_time(void)
{
	struct timeval	curr_time;
	long			timestamp;

	gettimeofday(&curr_time, NULL);
	timestamp = curr_time.tv_sec * 1000 + curr_time.tv_usec / 1000;
	return (timestamp);
}

/**
 * Pauses execution for a specified duration while
 * checking a termination condition.
 * 
 * The function records the start time, then repeatedly
 * sleeps for 500 microseconds until the elapsed time
 * reaches `msec` or until a termination condition (`is_game_over`) is met.
 *
 * @param msec Duration in milliseconds to pause.
 * @param table Pointer to a `t_table` structure containing the
 * 				termination condition and mutex.
 */
void	ft_usleep(int msec, t_table *table)
{
	long	usleep_start;

	usleep_start = get_curr_time();
	while (get_curr_time() - usleep_start < msec
		&& atomic_get(table->mtx_act, (long*) &table->is_game_over) == 0)
		usleep(500);
}

/**
 * Calculates and adjusts the action gap time for philosophers.
 *
 * This function computes the time gap (wait time) between actions 
 * based on the time to die, eat, and sleep, ensuring that the gap 
 * time is non-negative.
 */
void	set_action_gap(t_timing *t)
{
	t->action_gap = (t->die - (t->eat + t->sleep)) / 2;
	if (t->action_gap < 0)
		t->action_gap = 0;
}

/**
 * Sets the initialization time for the table based on the number
 * of created philosopher threads.
 *
 * This function updates the `timing.start` field in the `t_table` structure.
 * If the number of successfully created philosopher threads (`i`)
 * matches the total number of philosophers (`table->size`),
 * it sets `timing.start` to the current time. Otherwise, it sets `timing.start` 
 * to -1 to indicate that not all threads were created successfully.
 *
 * @param table Pointer to the table structure containing
 * 				the initialization time and mutex.
 * @param i Number of philosopher threads successfully created.
 */
void	set_start_time(t_table *table, size_t i)
{
	if (i != table->size)
	{
		table->timing.start = -1;
		return ;
	}
	table->timing.start = get_curr_time();
}

/**
 * Waits for the initialization time to be set and updates
 * the philosopher's last meal time.
 *
 * @param philo Pointer to the philosopher's data structure.
 * @return 1 if initialization time is -1, otherwise 0.
 */
int	wait_for_init_time_is_set(t_philo *philo)
{
	t_table	*table;

	table = philo->table;
	philo->last_meal_time = atomic_get(table->mtx_act, &table->timing.start);
	if (philo->last_meal_time == -1)
		return (1);
	return (0);
}
