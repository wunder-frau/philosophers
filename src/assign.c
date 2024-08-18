/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assign.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: istasheu <istasheu@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 08:53:11 by istasheu          #+#    #+#             */
/*   Updated: 2024/08/18 09:47:33 by istasheu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/**
 * Assign left and right forks to an ID phisopher.
 */
static void	assign_forks(const t_table *table, t_philo *philo)
{
	philo->forks[1] = &(table->mtx_forks[philo->id]);
	philo->forks[0] = &(table->mtx_forks[(philo->id + table->size - 1) % table->size]);
	if (philo->id + 1 == table->size)
		swap(philo->forks[0], philo->forks[1]);
}

bool	allocate_philosophers(t_table *table, size_t size)
{
	t_philo	*philosophers;
	size_t	i;

	philosophers = ft_calloc(size, sizeof(t_philo));
	if (!philosophers)
		return (false);
	i = 0;
	while (i < size)
	{
		philosophers[i].id = i;
		philosophers[i].table = table;
		assign_forks(table, &philosophers[i]);
		i++;
	}
	table->philosophers = philosophers;
	return (true);
}

bool	allocate_threads(t_table *table)
{
	table->monitor = ft_calloc(1, sizeof(pthread_t));
	if (!table->monitor)
		return (false);
	table->threads = ft_calloc(table->size, sizeof(pthread_t));
	if (!table->threads)
	{
		free(table->monitor);
		return (false);
	}
	return (true);
}

/**
 * Allocate table's arrays.
 */
bool	allocate(t_table *table)
{
	if (!allocate_mutexes(&(table->mtx_forks), table->size))
		return (false);
	if (!allocate_mutexes(&(table->mtx_act), 1))
		return (false);
	if (!allocate_philosophers(table, table->size))
		return (false);
	if (!allocate_threads(table))
	{
		destroy_and_free(table);
		return (false);
	}
	return (true);
}
