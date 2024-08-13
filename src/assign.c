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
	long	i;

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
bool	allocate_mutexes(pthread_mutex_t **mutexes, long size)
{
	pthread_mutex_t	*tmp;
	long			i;

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

bool	allocate_philos(t_table *table, long size)
{
	t_philo	*philosophers;
	long	i;

	philosophers = ft_calloc(size, sizeof(t_philo));
	if (!philosophers)
		return (false);
	i = 0;
	while (i < size)
	{
		philosophers[i].id = i;
		philosophers[i].table = table;
		assign_forks(table, &philosophers[i]);
		philosophers[i].mtx_philo = &table->mtx_philo[i];
		printf("Initialized philosopher %zu with ID %zu\n", i, philosophers[i].id);
		i++;
	}
	table->philosophers = philosophers;
	return (true);
}
// t_philo *allocate_philos(const size_t size, t_locks *locks, t_intervals intervals) {
//     t_philo *philos;
//     size_t i;

//     philos = calloc(size, sizeof(t_philo));
//     if (!philos)
//         return (NULL);

//     i = 0;
//     while (i < size) {
//         philos[i].id = i;
//         philos[i].action = THINK;
//         philos[i].left = NULL;
//         philos[i].right = NULL;
//         philos[i].locks = locks;
//         philos[i].intervals = intervals;
//         philos[i].last_meal_time = get_current_time();
//         printf("Initialized philosopher %zu with ID %zu\n", i, philos[i].id);
//         ++i;
//     }
//     return (philos);
// }

/**
 * Allocate table's arrays.
 */
bool	allocate(t_table *table)
{
	if (!allocate_mutexes(&(table->mtx_forks), table->size))
		return (false);
	if (!allocate_mutexes(&(table->mtx_philo), table->size))
		return (false);
	if (!allocate_mutexes(&(table->mtx_death), 1))
		return (false);
	if (!allocate_philos(table, table->size))
		return (false);
	return (true);
}

// /**
//  * Set initial philosophers' actions and distribute forks.
//  */
// void assign(t_table *table)
// {
// 	size_t i;

// 	i = 0;
// 	while (i < table->size)
// 	{
// 		assign_forks(table, &(table->philosophers[i]));
// 		++i;
// 	}
// }