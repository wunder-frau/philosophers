#include "philo.h"

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
static void	assign_forks(const t_table *table, t_philo *philo)
{
	printf("%zu philosopher will recieve {%zu, %zu} forks\n", philo->id, philo->id, (philo->id + table->size - 1) % table->size);
	philo->mtx_right = &(table->mtx_forks[philo->id]);
	philo->mtx_left = &(table->mtx_forks[(philo->id + table->size - 1) % table->size]);
	if (philo->id + 1 == table->size)
		swap(philo->mtx_left, philo->mtx_right);
}

void	destroy(pthread_mutex_t *mutexes, size_t n)
{
	size_t	i;

	if (!mutexes)
		return ;

	i = 0;
	while (i < n)
	{
		pthread_mutex_destroy(&mutexes[i]);
		i++;
	}
	free(mutexes);
}

/**
 * Initialise mutexes, i.e. mutexes must be allocated.
 */
bool	allocate_mutexes(pthread_mutex_t **mutexes, size_t size)
{
	pthread_mutex_t	*tmp;
	size_t			i;

	tmp = ft_calloc(size, sizeof(pthread_mutex_t));
	if (!tmp)
		return (false);
	i = 0;
	while (i < size)
	{
		if (pthread_mutex_init(&tmp[i], NULL) != 0)
		{
			destroy(tmp, i);
			return (false);
		}
		i++;
	}
	*mutexes =  tmp;
	return (true);
}

bool	allocate_philosophers(t_table *table, size_t size)
{
	t_philo	*philosophers;
	size_t	i;

	philosophers = ft_calloc(size, sizeof(t_philo));
	if (!philosophers)
		return (false);
	i = 0;
	while (i < size)
	{
		philosophers[i].id = i;
		philosophers[i].table = table;
		assign_forks(table, &philosophers[i]);
		philosophers[i].mtx_philo = &table->mtx_philosophers[i];
		printf("Initialized philosopher %zu with ID %zu\n", i, philosophers[i].id);
		i++;
	}
	table->philosophers = philosophers;
	return (true);
}

bool	allocate_threads(t_table *table)
{
	table->monitor = ft_calloc(1, sizeof(pthread_t));
	if (!table->monitor)
		return (false);
	table->threads = ft_calloc(table->size, sizeof(pthread_t));
	if (!table->threads)
	{
		free(table->monitor);
		return (false);
	}
	return (true);
}

/**
 * Allocate table's arrays.
 */
bool	allocate(t_table *table)
{
	if (!allocate_mutexes(&(table->mtx_forks), table->size))
		return (false);
	if (!allocate_mutexes(&(table->mtx_philosophers), table->size))
		return (false);
	if (!allocate_mutexes(&(table->mtx_act), 1))
		return (false);
	if (!allocate_philosophers(table, table->size))
		return (false);
	if (!allocate_threads(table))
	{
		destroy_and_free(table);
		return (false);
	}
	return (true);
}
