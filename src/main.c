/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: istasheu <istasheu@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 02:14:29 by istasheu          #+#    #+#             */
/*   Updated: 2024/08/19 02:14:30 by istasheu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_table	table;

	memset(&table, 0, sizeof(table));
	if (!parse_and_assign_args(argc, argv, &table))
		return (1);
	if (!allocate(&table))
		return (1);
	if (!init(&table))
	{
		destroy_and_free(&table);
		return (1);
	}
	destroy_and_free(&table);
	return (0);
}
