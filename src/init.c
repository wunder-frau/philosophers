#include "philo.h"

/**
 * Waits for all philosopher threads to complete.
 * Iterates through the list of threads and uses `pthread_join` 
 * to wait for each thread to finish its execution.
 */
static void	join_pthreads(t_table *table, int size)
{
	int	i;

	i = 0;
	pthread_join(*(table->monitor), NULL);
	while (i < size)
	{
		pthread_join(table->threads[i], NULL);
		i++;
	}
}

/**
 * Initializes philosopher threads and sets the init_time time.
 * Attempts to create all philosopher threads using `pthread_create`.
 * If thread creation fails, it breaks out of the loop and sets the init_time time to -1.
 * If all threads are created successfully, it sets the init_time time and waits for all threads to finish.
 *
 * @param table Pointer to the table structure containing thread and mutex information.
 * @return True if all threads were successfully created and initialized, otherwise false.
 */
bool	init(t_table *table)
{
	size_t	i;

	if (pthread_create(table->monitor, NULL, monitoring, (void *) table) != 0)
		return (false);
	i = 0;
	while (i < table->size)
	{
		if (pthread_create(&table->threads[i], NULL,
			act, (void *)&((table->philosophers)[i])) != 0)
		{
			ft_putstr_fd("Error: philosopher thread_create failed\n", 2);
			break ;
		}
		i++;
	}
	set_init_time(table, i);
	join_pthreads(table, i);
	return (i == table->size);
}
