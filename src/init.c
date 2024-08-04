#include "philo.h"

static void	*act(void *philo_ptr) {
	t_philo	*philo;

	philo = (t_philo *)philo_ptr;
	pthread_mutex_lock(&philo->locks->print);
	printf("%zu is acting\n", philo->id);
	pthread_mutex_unlock(&philo->locks->print);
	return (NULL);
}

void init(t_table *table)
{
	size_t	i;

	i = 0;
	while (i < table->size)
	{
		pthread_create(&table->philosophers[i].thread, NULL, &act, (void *)&table->philosophers[i]);
		/*{
			pthread_mutex_lock(&table->locks.print);
			printf("%zu", table->philosophers[i].id);
			pthread_mutex_unlock(&table->locks.print);
		}*/
		++i;
	}
	i = 0;
	while (i < table->size)
	{
		if (pthread_join(table->philosophers[i].thread, NULL))
			printf("Error: pthread_join failed\n");
		++i;
	}
}
