#include "philo.h"

int main(int argc, char **argv)
{
	t_intervals	intervals;
	t_table 		table;

	if (argc != 5)
	{
		fprintf(stderr, "Usage: %s number_of_philosophers time_to_die time_to_eat time_to_sleep\n", argv[0]);
		return 1;
	}
	intervals.start = get_current_time();
	intervals.die = (time_t) atol(argv[2]);
	intervals.eat = (time_t) atol(argv[3]);
	intervals.sleep = (time_t) atol(argv[4]);
	table = allocate(intervals, atoi(argv[1]));
	assign(&table);
	init(&table);

	if (table.philosophers)
		free(table.philosophers);
	if (table.forks)
		free(table.forks);
	return (0);
}
