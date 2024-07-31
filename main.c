#include "philo.h"

int main(int argc, char **argv)
{
	if (argc != 5)
	{
		fprintf(stderr, "Usage: %s number_of_philosophers time_to_die time_to_eat time_to_sleep\n", argv[0]);
		return 1;
	}
	//TODO: 3. Finish t_intervals initialisation from argv
	t_intervals	intervals;
	intervals.die = (time_t) atol(argv[2]);
	intervals.eat = (time_t) atol(argv[3]);
	intervals.sleep = (time_t) atol(argv[4]);
	// intervals.die = argv[2];
	// intervals.? = ...;

	//TODO: 4. mplement ft_init (callac, malloc, huek)
	// ft_init(intervals, count); // what is size here?

	// ---

	// free(table->philosophers);
	// free(table->forks);
	return (0);
}
