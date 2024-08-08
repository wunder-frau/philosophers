#include "philo.h"

static bool	do_eat(t_philo *philo)
{
	pthread_mutex_lock(philo->right);
	log_action(philo, "has taken right fork");

	pthread_mutex_lock(philo->left);
	log_action(philo, "has taken left fork");

	if (is_dead(philo))
	{
		pthread_mutex_unlock(philo->right);
		pthread_mutex_unlock(philo->left);
		return (false);
	}

	philo->action = EAT;
	pthread_mutex_lock(&philo->locks->eat);
	log_action(philo, "is eating");
	philo->last_meal_time = get_current_time();
	pthread_mutex_unlock(&philo->locks->eat);

	ft_safe_usleep(philo->intervals.eat, philo);
	pthread_mutex_unlock(philo->left);
	pthread_mutex_unlock(philo->right);

	return (true);
}

static bool	do_sleep(t_philo *philo)
{
	if (is_dead(philo))
		return (false);
	philo->action = SLEEP;
	log_action(philo, "is sleeping");
	ft_safe_usleep(philo->intervals.sleep, philo);
	return (true);
}

static bool	do_think(t_philo *philo)
{
	if (is_dead(philo))
		return (false);
	philo->action = THINK;
	log_action(philo, "is thinking");
	return (true);
}

/**
 * Executes the main routine for a philosopher thread.
 * 
 * @param philo_ptr:	A pointer to the philosopher structure,
 * 						passed as a `void *` to comply with `pthread_create` requirements.
 * @return: Returns NULL when the philosopher's routine is complete or if the philosopher has died.
 */

void	*act(void *philo_ptr)
{
	t_philo *philo;
	
	philo = (t_philo *)philo_ptr;

	if (philo->id % 2 == 1)
	{
		printf("Philosopher %zu is thinking initially\n", philo->id);
		if (do_think(philo) == 1)
			return (NULL);
		ft_safe_usleep(philo->intervals.eat / 2, philo);
	}

	while (!is_dead(philo))
	{
		if (philo->action == EAT)
		{
			printf("Philosopher %zu is about to eat\n", philo->id + 1);
			if (!do_eat(philo))
				return (NULL);
			philo->action = SLEEP;
			printf("Philosopher %zu finished eating, will sleep next\n", philo->id + 1);
		}
		else if (philo->action == SLEEP)
		{
			printf("Philosopher %zu is about to sleep\n", philo->id + 1);
			if (!do_sleep(philo))
				return (NULL);
			philo->action = THINK;
			printf("Philosopher %zu finished sleeping, will think next\n", philo->id + 1);
		}
		else if (philo->action == THINK)
		{
			printf("Philosopher %zu is about to think\n", philo->id + 1);
			if (!do_think(philo))
				return (NULL);
			philo->action = EAT;
			printf("Philosopher %zu finished thinking, will eat next\n", philo->id + 1);
		}
		else if (philo->action == DEAD)
		{
			printf("Philosopher %zu has died and will exit\n", philo->id + 1);
			return (NULL);
		}
	}

	return (NULL);
}
