#include "philo.h"

/**
 * TODO: add validation logic later...
 */
bool	is_args_valid(int argc, char **argv, t_table *table)
{
	if (argc != 5)
	{
		ft_putstr_fd("Usage: %s number_of_philosophers time_to_die time_to_eat time_to_sleep\n", 2);
		exit(1);
	}
	table->size = ft_atol(argv[1]);
	table->die = (t_time)ft_atol(argv[2]);
	table->eat = (t_time)ft_atol(argv[3]);
	table->sleep = (t_time)ft_atol(argv[4]);
	table->start = get_current_time();
	if (table->size < 1 || table->die < 1 || table->eat < 1 || table->sleep < 1)
	{
		ft_putstr_fd("Error: All arguments must be positive integers.\n", 2);
		exit(1);
	}
	return (true);
}

int main(int argc, char **argv)
{
	t_table	table;

	ft_memset(&table, 0, sizeof(table));
	is_args_valid(argc, argv, &table);
	//table = allocate(intervals, atoi(argv[1]));
	//assign(&table);
	//init(&table);
	//destroy_and_free(&table);
	return (0);
}
