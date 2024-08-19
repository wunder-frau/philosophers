/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy_and_free.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: istasheu <istasheu@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 02:14:02 by istasheu          #+#    #+#             */
/*   Updated: 2024/08/19 02:14:03 by istasheu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	destroy_and_free(t_table *table)
{
	if (table->philosophers)
		free(table->philosophers);
	if (table->mtx_forks)
		destroy(table->mtx_forks, table->size);
	if (table->mtx_act)
		destroy(table->mtx_act, 1);
	if (table->monitor)
		free(table->monitor);
	if (table->threads)
		free(table->threads);
}
