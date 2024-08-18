#include "philo.h"

int	main(int argc, char **argv)
{
	t_table	table;

	memset(&table, 0, sizeof(table));
	if (!is_args_valid(argc, argv, &table))
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
