#include "philo.h"

/**
 * Reads a value from a variable with mutex protection.
 *
 * @param mutex Pointer to the mutex used for synchronization.
 * @param variable Pointer to the variable whose value is read.
 * @return The value of the variable.
 */
long	atomic_get(pthread_mutex_t *mutex, long *variable)
{
	long	value;

	pthread_mutex_lock(mutex);
	value = *variable;
	pthread_mutex_unlock(mutex);
	return (value);
}

/**
 * Writes a value to a variable with mutex protection.
 *
 * @param mutex Pointer to the mutex used for synchronization.
 * @param variable Pointer to the variable to which the value is written.
 * @param value The value to be written.
 */
void	atomic_set(pthread_mutex_t *mutex, long *variable, long value)
{
	pthread_mutex_lock(mutex);
	*variable = value;
	pthread_mutex_unlock(mutex);
}