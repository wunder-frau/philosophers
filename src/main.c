#include "philo.h"

/**
 * Allocate table's arrays.
 * 
 * Each philosepher has initial state THINKING.
 * FIXME: Should it be like this? This is definately not EATING, since it requires to have two forks.
 */
t_table ft_alloc(const t_intervals intervals, size_t size)
{
	t_table table;
	table.size = size;
	table.forks = malloc(size * sizeof(pthread_mutex_t));
	table.philosophers = malloc(size * sizeof(t_philosopher));
	while (size)
	{
		table.philosophers[size].id = table.size - size + 1;
		table.philosophers[size].state = THINKING;
		table.philosophers[size].intervals = intervals;
		table.philosophers[size].left = NULL;
		table.philosophers[size].right = NULL;
		--size;
	}
	return (table);
}

int main(int argc, char **argv)
{
	t_intervals	intervals;
	t_table 		table;

	if (argc != 5)
	{
		fprintf(stderr, "Usage: %s number_of_philosophers time_to_die time_to_eat time_to_sleep\n", argv[0]);
		return 1;
	}

	intervals.die = (time_t) atol(argv[2]);
	intervals.eat = (time_t) atol(argv[3]);
	intervals.sleep = (time_t) atol(argv[4]);
	table = ft_alloc(intervals, atoi(argv[1]));

	// ---

	free(table.philosophers);
	free(table.forks);
	return (0);
}
