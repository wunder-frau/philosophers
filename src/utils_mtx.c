/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_mtx.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: istasheu <istasheu@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 02:15:04 by istasheu          #+#    #+#             */
/*   Updated: 2024/08/19 02:15:05 by istasheu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	swap(pthread_mutex_t *a, pthread_mutex_t *b)
{
	pthread_mutex_t	tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

void	destroy(pthread_mutex_t *mutexes, size_t n)
{
	size_t	i;

	if (!mutexes)
		return ;
	i = 0;
	while (i < n)
	{
		pthread_mutex_destroy(&mutexes[i]);
		i++;
	}
	free(mutexes);
}

/**
 * Initialise mutexes, i.e. mutexes must be allocated.
 */
bool	allocate_mutexes(pthread_mutex_t **mutexes, size_t size)
{
	pthread_mutex_t	*tmp;
	size_t			i;

	tmp = ft_calloc(size, sizeof(pthread_mutex_t));
	if (!tmp)
		return (false);
	i = 0;
	while (i < size)
	{
		if (pthread_mutex_init(&tmp[i], NULL) != 0)
		{
			destroy(tmp, i);
			return (false);
		}
		i++;
	}
	*mutexes = tmp;
	return (true);
}
