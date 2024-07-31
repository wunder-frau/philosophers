#include "philo.h"

/**
 * Allocate table's arrays.
 */
t_table ft_alloc(const t_intervals intervals, size_t size)
{
	t_table table;
	table.size = size;
	table.forks = malloc(size * sizeof(pthread_mutex_t));
	table.philosophers = malloc(size * sizeof(t_philosopher));
	if (!table.forks || !table.philosophers)
	{
		free(table.forks);
		free(table.philosophers);
		table.size = 0;
		return table;
	}
	while (size)
	{
		table.philosophers[size].id = (table.size - size) + 1;
		table.philosophers[size].state = THINKING; // ft_init
		table.philosophers[size].intervals = intervals;
		table.philosophers[size].left = NULL;
		table.philosophers[size].right = NULL;
		printf("Initialized philosopher %zu with ID %zu\n", size, table.philosophers[size].id);
		--size;
	}
	return (table);
}

/**
 * Set initial philosophers' states and distribute forks.
 */
// ft_init
void ft_init(t_table *table)
{
	size_t i;
	size_t j;

	i = 0;
	j = 0;
	while (i < table->size)
	{
		if (j < table->size)
		{
			table->philosophers[i].right = &(table->forks[j]);
			if (j + 1 < table->size)
			{
				table->philosophers[i].left = &(table->forks[j + 1]);
			}
			j++;
		}
		if (table->philosophers[i].right != NULL && table->philosophers[i].left != NULL)
		{
			table->philosophers[i].state = EATING;
			printf("Philosopher %zu is in state EATING\n", i + 1);
		}
		else
		{
			table->philosophers[i].state = THINKING;
			printf("Philosopher %zu is in state THINKING\n", i + 1);
		}
		i++;
	}
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
	ft_init(&table);
	// ---

	free(table.philosophers);
	free(table.forks);
	return (0);
}
