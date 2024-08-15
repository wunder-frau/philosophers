#include "philo.h"

static void	increment_satiated_count(t_table *table)
{
	pthread_mutex_lock(table->mtx_act);
	table->satiation_count++;
	pthread_mutex_unlock(table->mtx_act);
}

static void	handle_single_philos_act(t_philo *philo)
{
	log_action(philo, get_current_time(), "is thinking\n");
	pthread_mutex_lock(philo->mtx_right);
	log_action(philo, get_current_time(), "has taken a fork\n");
	ft_usleep(philo->table->die, philo->table);
	pthread_mutex_unlock(philo->mtx_right);
}

static int	do_eat(t_philo *philo)
{
	int	status;

	pthread_mutex_lock(philo->mtx_right);
	if (log_action(philo, get_current_time(), "has taken a fork\n") == 1)
	{
		pthread_mutex_unlock(philo->mtx_right);
		return (1);
	}
	pthread_mutex_lock(philo->mtx_left);
	if (log_action(philo, get_current_time(), "has taken a fork\n") == 1)
	{
		pthread_mutex_unlock(philo->mtx_right);
		pthread_mutex_unlock(philo->mtx_left);
		return (1);
	}
	atomic_set(philo->mtx_philo, &philo->last_meal_time, get_current_time());
	status = log_action(philo, philo->last_meal_time, "is eating\n");
	if (status == 0)
		ft_usleep(philo->table->eat, philo->table);
	philo->meal_count++;
	if (philo->meal_count == philo->table->meal_count)
		increment_satiated_count(philo->table);
	pthread_mutex_unlock(philo->mtx_right);
	pthread_mutex_unlock(philo->mtx_left);
	return (status);
}

static int	handle_philososophers_act(t_philo *philo)
{
	if (log_action(philo, get_current_time(), "is thinking\n") == 1)
		return (1);
	if (philo->id % 2 != 0 && philo->meal_count == 0)
		ft_usleep(philo->table->eat / 2, philo->table);
	if (philo->table->size % 2 != 0
		&& philo->meal_count != 0)
		ft_usleep(philo->table->action_gap, philo->table);
	if (do_eat(philo) == 1)
		return (1);
	if (log_action(philo, get_current_time(), "is sleeping\n") == 1)
		return (1);
	ft_usleep(philo->table->sleep, philo->table);
	return (0);
}

void	*act(void *philo_ptr)
{
	t_philo	*philo;

	philo = (t_philo *)philo_ptr;
	if (wait_for_init_time_is_set(philo) == 1)
		return (NULL);
	if (philo->table->size == 1)
		handle_single_philos_act(philo);
	else
	{
		while (1)
			if (handle_philososophers_act(philo) == 1)
				break ;
	}
	return (NULL);
}
