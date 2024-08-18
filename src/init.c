/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: istasheu <istasheu@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 02:14:13 by istasheu          #+#    #+#             */
/*   Updated: 2024/08/19 02:14:16 by istasheu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/**
 * Waits for all philosopher threads to complete.
 * Iterates through the list of threads and uses `pthread_join` 
 * to wait for each thread to finish its execution.
 */
static void	join_pthreads(t_table *table, int size)
{
	int	i;

	i = 0;
	pthread_join(*(table->monitor), NULL);
	while (i < size)
	{
		pthread_join(table->threads[i], NULL);
		i++;
	}
}

/**
 * Initializes philosopher threads and sets the timing.start time.
 * Attempts to create all philosopher threads using `pthread_create`.
 * If thread creation fails, it breaks out of the loop and sets the 
 * timing.start time to -1. If all threads are created successfully,
 * it sets the timing.start time and waits for all threads to finish.
 *
 * @param table Pointer to the table structure containing
 * 				thread and mutex information.
 * @return True if all threads were successfully
 *			created and initialized, otherwise false.
 */
bool	init(t_table *table)
{
	size_t	i;

	pthread_mutex_lock(table->mtx_act);
	if (pthread_create(table->monitor, NULL, monitoring, (void *) table) != 0)
		return (false);
	i = 0;
	while (i < table->size)
	{
		if (pthread_create(&table->threads[i], NULL,
				act, (void *)&((table->philosophers)[i])) != 0)
		{
			ft_putstr_fd("Error: philosopher thread_create failed\n", 2);
			break ;
		}
		i++;
	}
	set_start_time(table, i);
	pthread_mutex_unlock(table->mtx_act);
	join_pthreads(table, i);
	return (i == table->size);
}
