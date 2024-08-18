#include "philo.h"

/**
 * Sets the initialization time for the table based on the number of created philosopher threads.
 *
 * This function updates the `init_time` field in the `t_table` structure. If the number of
 * successfully created philosopher threads (`i`) matches the total number of philosophers 
 * (`table->size`), it sets `init_time` to the current time. Otherwise, it sets `init_time` 
 * to -1 to indicate that not all threads were created successfully.
 *
 * @param table Pointer to the table structure containing the initialization time and mutex.
 * @param i Number of philosopher threads successfully created.
 */
void	set_init_time(t_table *table, size_t i)
{
	if (i == table->size)
		table->init_time = get_current_time();
	else
		table->init_time = -1;
}

/**
 * Waits for the initialization time to be set and updates the philosopher's last meal time.
 *
 * @param philo Pointer to the philosopher's data structure.
 * @return 1 if initialization time is -1, otherwise 0.
 */
int	wait_for_init_time_is_set(t_philo *philo)
{
	t_table	*table;

	table = philo->table;
	philo->last_meal_time = atomic_get(table->mtx_act, &table->init_time);
	if (philo->last_meal_time == -1)
		return (1);
	return (0);
}