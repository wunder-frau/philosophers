/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: istasheu <istasheu@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 02:14:56 by istasheu          #+#    #+#             */
/*   Updated: 2024/08/19 09:25:00 by istasheu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_actions	create_actions(void)
{
	t_actions	actions;

	actions.taken_fork = "has taken a fork\n";
	actions.died = "has died\n";
	actions.sleeping = "is sleeping\n";
	actions.eating = "is eating\n";
	actions.thinking = "is thinking\n";
	return (actions);
}

/**
 * Delays a philosopher's actions to ensure proper
 * timing and avoid conflicts.
 * 
 * - If the philosopher has an odd ID and hasn't eaten yet,
 * they will wait for a specified action gap to stagger
 * their actions compared to others.
 *
 *  - If the table has an odd number of philosophers and
 * this philosopher has eaten, they will also wait for
 * the same action gap to balance timing between actions.
 * 
 * The action gap used for the delay is calculated
 * by the `set_action_gap` function.
 * @param philo Pointer to the philosopher structure
 * 				that includes the timing settings.
 */
void	set_delay_for_odd(t_philo *philo)
{
	if (philo->id % 2 != 0 && philo->meal_count == 0)
		ft_usleep(philo->table->timing.action_gap, philo->table);
	else if (philo->table->size % 2 != 0 && philo->meal_count != 0)
		ft_usleep(philo->table->timing.action_gap, philo->table);
}
