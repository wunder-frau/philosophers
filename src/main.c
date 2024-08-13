#include "philo.h"

/**
 * TODO: add validation logic later...
 */
bool	is_args_valid(int argc, char **argv, t_table *table)
{
	if (argc != 5 && argc != 6)
	{
		ft_putstr_fd("Usage: %s number_of_philosophers time_to_die time_to_eat time_to_sleep\n", 2);
		exit(1);
	}
	table->size = ft_atol(argv[1]);
	table->die = (t_time)ft_atol(argv[2]);
	table->eat = (t_time)ft_atol(argv[3]);
	table->sleep = (t_time)ft_atol(argv[4]);
	if (argc == 6)
		table->meal_count = ft_atol(argv[5]);
	else
		table->meal_count = -1;
	if (table->size < 1 || table->die < 1 || table->eat < 1 || table->sleep < 1)
	{
		ft_putstr_fd("Error: All arguments must be positive integers.\n", 2);
		return (false);
	}
	table->action_gap = calculate_action_gap(table->die, table->eat, table->sleep);
	printf("%zu\n", table->action_gap);
	return (true);
}

int	main(int argc, char **argv)
{
	t_table	table;

	memset(&table, 0, sizeof(table));
	if (!is_args_valid(argc, argv, &table))
		return(1);
	if (!allocate(&table))
		return (1);
	if (!init(&table))
	{
		destroy_and_free(&table);
		return (1);
	}
	return (0);
}
