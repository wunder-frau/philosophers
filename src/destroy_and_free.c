#include "philo.h"

void	destroy_and_free(t_table *table)
{
	if (table->philosophers)
		free(table->philosophers);
	if (table->mtx_philosophers)
		destroy(table->mtx_philosophers, table->size);
	if (table->mtx_forks)
		destroy(table->mtx_forks, table->size);
	if (table->mtx_act)
		destroy(table->mtx_act, 1);
	if (table->monitor)
		free(table->monitor);
	if (table->threads)
		free(table->threads);
}