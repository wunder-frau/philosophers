#include "philo.h"

static void	init_pthreads(pthread_t	*monitor, t_table *table)
{
	size_t	i;

	if (pthread_create(monitor, NULL, &monitoring, (void *)table))
	{
		printf("Error: monitoring thread_creat failed\n");
		destroy_and_free(table);
		return ;
	}
	i = 0;
	while (i < table->size)
	{
		if (pthread_create(&table->philosophers[i].thread, NULL,
			&act, (void *)&table->philosophers[i]))
		{
			printf("Error: philosopher thread_create failed\n");
			// destroy_and_free(table);
			// return ;
			pthread_mutex_lock(&table->philosophers[i].locks->death);
			table->philosophers[i].action = DEAD;
			log_action(&table->philosophers[i], "has died");
			pthread_mutex_unlock(&table->philosophers[i].locks->death);
			break ;
		}
		++i;
	}
}

static void	join_pthreads(pthread_t	*monitor, t_table *table)
{
	size_t	i;

	if (pthread_join(*monitor, NULL) != 0)
	{
		printf("Error: monitor_join falied\n");
		destroy_and_free(table);
		return ; // (clean_all(philo->table, philo));
	}
	i = 0;
	while (i < table->size)
	{
		if (pthread_join(table->philosophers[i].thread, NULL))
			printf("Error: pthread_join failed\n");
		++i;
	}
}

void init(t_table *table)
{
	pthread_t	monitor;

	table->game_over = false;
	init_pthreads(&monitor, table);
	join_pthreads(&monitor, table);
}
