#include "philo.h"

/**
 * Allocate table's arrays.
 */
t_table allocate(const t_intervals intervals, size_t size)
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
		return (table);
	}
	while (size)
	{
		table.philosophers[table.size - size].id = table.size - size;
		table.philosophers[table.size - size].state = THINKING; // assign
		table.philosophers[table.size - size].intervals = intervals;
		table.philosophers[table.size - size].left = NULL;
		table.philosophers[table.size - size].right = NULL;
		printf("Initialized philosopher %zu with ID %zu\n", table.size - size, table.philosophers[table.size - size].id);
		--size;
	}
	return (table);
}

static void	swap(pthread_mutex_t *a, pthread_mutex_t *b)
{
	pthread_mutex_t	tmp;
	tmp = *a;
	*a = *b;
	*b = tmp;
}

/**
 * Assign left and right forks to an ID phisopher.
 */
static void	assign_forks(const t_table *table, t_philosopher *philo)
{
	size_t count;

	count = table->size;
	printf("%zu philosopher's recieving {%zu, %zu} forks\n", philo->id, philo->id, (philo->id + count - 1) % count);
	philo->right = &(table->forks[philo->id]);
	philo->left = &(table->forks[(philo->id + count - 1) % count]);
	if (philo->id + 1 == count)
		swap(philo->left, philo->right);
}

/**
 * Set initial philosophers' states and distribute forks.
 */
void assign(t_table *table)
{
	size_t i;

	i = 0;
	while (i < table->size) {
		assign_forks(table, &(table->philosophers[i]));
		++i;
	}
}

long	get_current_timestamp(void)
{
	struct timeval curr_time;

	gettimeofday(&curr_time, NULL);
	return ((long)curr_time.tv_sec * 1000 + (long)curr_time.tv_usec / 1000);
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
	intervals.timestamp = get_current_timestamp();
	intervals.die = (time_t) atol(argv[2]);
	intervals.eat = (time_t) atol(argv[3]);
	intervals.sleep = (time_t) atol(argv[4]);
	table = allocate(intervals, atoi(argv[1]));
	assign(&table);
	// ---

	free(table.philosophers);
	free(table.forks);
	return (0);
}
