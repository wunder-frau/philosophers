/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: istasheu <istasheu@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 02:15:25 by istasheu          #+#    #+#             */
/*   Updated: 2024/08/19 02:17:02 by istasheu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

static bool	str_to_long_if_numeric(char *str)
{
	long	len;

	len = ft_strlen(str);
	if (len > 8)
	{
		ft_putstr_fd("Error: Number must have no more than 8 digits.\n", 2);
		exit(1);
	}
	while (*str)
	{
		if (!ft_isdigit((unsigned char)*str))
		{
			ft_putstr_fd("Error: Non-numeric of negative character found.\n", 2);
			exit(1);
		}
		str++;
	}
	return (true);
}

static bool	is_args_valid(int argc, char **argv)
{
	int	i;

	if (argc != 5 && argc != 6)
	{
		ft_putstr_fd("Usage: %s number_of_philosophers time_to_die "
			"time_to_eat time_to_sleep [optional: number_of_meals]\n", 2);
		exit(1);
	}
	i = 1;
	while (i < argc)
	{
		if (!str_to_long_if_numeric(argv[i]))
			return (false);
		i++;
	}
	return (true);
}

bool	parse_and_assign_args(int argc, char **argv, t_table *table)
{
	if (is_args_valid(argc, argv) == true)
	{
		table->size = ft_atol(argv[1]);
		table->timing.die = (t_time)ft_atol(argv[2]);
		table->timing.eat = (t_time)ft_atol(argv[3]);
		table->timing.sleep = (t_time)ft_atol(argv[4]);
		if (argc == 6)
			table->meal_count = ft_atol(argv[5]);
		else
			table->meal_count = -1;
	}
	return (true);
}
