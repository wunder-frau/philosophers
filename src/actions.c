/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: istasheu <istasheu@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 08:52:09 by istasheu          #+#    #+#             */
/*   Updated: 2024/08/19 09:37:17 by istasheu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	increment_satiated_count(t_table *table)
{
	pthread_mutex_lock(table->mtx_act);
	table->satiation_count++;
	pthread_mutex_unlock(table->mtx_act);
}

static void	handle_single_philos_act(t_philo *philo, t_actions *actions)
{
	log_action(philo, get_curr_time(), actions->thinking);
	pthread_mutex_lock(philo->forks[1]);
	log_action(philo, get_curr_time(), actions->taken_fork);
	ft_usleep(philo->table->timing.die, philo->table);
	pthread_mutex_unlock(philo->forks[1]);
}

static int	do_eat(t_philo *philo, t_actions *actions)
{
	int	status;

	pthread_mutex_lock(philo->forks[1]);
	if (log_action(philo, get_curr_time(), actions->taken_fork) == 1)
	{
		pthread_mutex_unlock(philo->forks[1]);
		return (1);
	}
	pthread_mutex_lock(philo->forks[0]);
	if (log_action(philo, get_curr_time(), actions->taken_fork) == 1)
	{
		pthread_mutex_unlock(philo->forks[1]);
		pthread_mutex_unlock(philo->forks[0]);
		return (1);
	}
	atomic_set(philo->table->mtx_act, &philo->last_meal_time, get_curr_time());
	status = log_action(philo, philo->last_meal_time, actions->eating);
	if (status == 0)
		ft_usleep(philo->table->timing.eat, philo->table);
	philo->meal_count++;
	if (philo->meal_count == philo->table->meal_count)
		increment_satiated_count(philo->table);
	pthread_mutex_unlock(philo->forks[1]);
	pthread_mutex_unlock(philo->forks[0]);
	return (status);
}

static int	handle_philososophers_act(t_philo *philo, t_actions *actions)
{
	if (log_action(philo, get_curr_time(), actions->thinking) == 1)
		return (1);
	set_delay_for_odd(philo);
	if (do_eat(philo, actions) == 1)
		return (1);
	if (log_action(philo, get_curr_time(), actions->sleeping) == 1)
		return (1);
	ft_usleep(philo->table->timing.sleep, philo->table);
	return (0);
}

void	*act(void *philo_ptr)
{
	t_philo		*philo;
	t_actions	actions;

	philo = (t_philo *)philo_ptr;
	actions = create_actions();
	if (wait_for_init_time_is_set(philo) == 1)
		return (NULL);
	if (philo->table->size == 1)
	{
		handle_single_philos_act(philo, &actions);
		return (NULL);
	}
	while (true)
	{
		if (handle_philososophers_act(philo, &actions) == 1)
			break ;
	}
	return (NULL);
}
