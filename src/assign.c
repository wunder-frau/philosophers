#include "philo.h"

static void	swap(pthread_mutex_t *a, pthread_mutex_t *b)
{
	pthread_mutex_t	*tmp;
	tmp = a;
	a = b;
	b = tmp;
}

void	destroy(pthread_mutex_t **mutexes, size_t n)
{
	size_t i;

	i = 0;
	while (i < n)
	{
		pthread_mutex_destroy(mutexes[i]);
		i++;
	}
	free(mutexes);
}

/**
 * Initialise mutexes, i.e. mutexes must be allocated.
 */
static pthread_mutex_t	*allocate_mutexes(const size_t size)
{
	pthread_mutex_t *mutexes;
	size_t i;

	mutexes = calloc(size, sizeof(pthread_mutex_t));
	if (!mutexes)
		return (NULL);
	i = 0;
	while (i < size)
	{
		if (pthread_mutex_init(&mutexes[i], NULL) != 0)
			destroy(&mutexes, size);
		i++;
	}
	return mutexes;
}

t_philo *allocate_philos(const size_t size, t_locks *locks, t_intervals intervals) {
    t_philo *philos;
    size_t i;

    philos = calloc(size, sizeof(t_philo));
    if (!philos)
        return (NULL);

    i = 0;
    while (i < size) {
        philos[i].id = i;
        philos[i].action = THINK;
        philos[i].left = NULL;
        philos[i].right = NULL;
        philos[i].locks = locks;
        philos[i].intervals = intervals;
        philos[i].last_meal_time = get_current_time();
        printf("Initialized philosopher %zu with ID %zu\n", i, philos[i].id);
        ++i;
    }
    return (philos);
}


/**
 * Assign left and right forks to an ID phisopher.
 */
static void	assign_forks(const t_table *table, t_philo *philo)
{
	printf("%zu philosopher will recieve {%zu, %zu} forks\n", philo->id, philo->id, (philo->id + table->size - 1) % table->size);
	philo->right = &(table->forks[philo->id]);
	philo->left = &(table->forks[(philo->id + table->size - 1) % table->size]);
	if (philo->id + 1 == table->size)
		swap(philo->left, philo->right);
}

/**
 * Allocate table's arrays.
 */
t_table allocate(const t_intervals intervals, size_t size)
{
	t_table table;

	table.size = 0;
	if (pthread_mutex_init(&table.locks.eat, NULL) != 0
		|| pthread_mutex_init(&table.locks.print, NULL) != 0
		|| pthread_mutex_init(&table.locks.dead, NULL) != 0)
		{
			destroy_and_free(&table);
			return (table);
		}
	table.forks = allocate_mutexes(size);
	if (table.forks == NULL)
	{
		destroy_and_free(&table);
		return (table);
	}
	table.intervals = intervals;
	table.philosophers = allocate_philos(size, &table.locks, intervals);
	if (table.philosophers == NULL)
	{
		destroy_and_free(&table);
		return (table);
	}
	table.size = size;
	return (table);
}

/**
 * Set initial philosophers' actions and distribute forks.
 */
void assign(t_table *table)
{
	size_t i;

	i = 0;
	while (i < table->size)
	{
		assign_forks(table, &(table->philosophers[i]));
		++i;
	}
}