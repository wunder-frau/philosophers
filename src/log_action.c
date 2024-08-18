/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   log_action.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: istasheu <istasheu@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 02:14:21 by istasheu          #+#    #+#             */
/*   Updated: 2024/08/19 02:14:24 by istasheu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/**
 * Log a philosopher's action with a time.
 */

bool	log_action(t_philo *philo, long time, const char *act_msg)
{
	t_table	*table;

	table = philo->table;
	pthread_mutex_lock(table->mtx_act);
	if (table->is_game_over == 0)
	{
		printf("%zu\t%zu\t%s", time - table->timing.start,
			philo->id + 1, act_msg);
		pthread_mutex_unlock(table->mtx_act);
		return (false);
	}
	pthread_mutex_unlock(table->mtx_act);
	return (true);
}
