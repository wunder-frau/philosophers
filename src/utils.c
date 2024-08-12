#include "philo.h"

bool is_dead(t_philo *philo) {
    t_time curr;

    pthread_mutex_lock(&philo->locks->eat);
    curr = get_current_time();
    if (curr >= philo->last_meal_time + philo->intervals.die) {
        if (philo->action != DEAD) {
            philo->action = DEAD;
            philo->table->game_over = true;
            log_action_death(philo, "has died");
        }
        pthread_mutex_unlock(&philo->locks->eat);
        return true;
    }
    else
		pthread_mutex_unlock(&philo->locks->eat);
    return false;
}



// bool	is_dead(t_philo *philo)
// {
// 	t_time curr;

// 	pthread_mutex_lock(&philo->locks->eat);
// 	curr = get_current_time();
// 	//printf("Philosopher %zu: curr = %ld, last_meal_time = %ld, die = %ld\n", philo->id, curr, philo->last_meal_time, philo->intervals.die);
// 	//if (curr >= philo->last_meal_time + philo->intervals.die)
// 	if (curr >= philo->last_meal_time + philo->intervals.die)
// 	{
// 		if (philo->action != DEAD)
// 		{
// 			//pthread_mutex_unlock(&philo->locks->eat);
// 			pthread_mutex_lock(&philo->locks->death);
// 			philo->action = DEAD;
// 			philo->table->game_over = true;
// 			log_action_death(philo, "has died");
// 			pthread_mutex_unlock(&philo->locks->death);
//     		pthread_mutex_unlock(&philo->locks->eat);
// 		}
// 		return (true);
// 	}
// 	pthread_mutex_unlock(&philo->locks->eat);
// 	return (false);
// }

bool check_death_flag(t_philo *philo)
{
	bool	is_game_over;

	pthread_mutex_lock(&philo->table->locks.death);
	is_game_over = philo->table->game_over;
	pthread_mutex_unlock(&philo->table->locks.death);
	return is_game_over;
}


// bool is_game_over(t_table *table) {
//     size_t i;

//     pthread_mutex_lock(&table->locks.death);
//     if (table->game_over) {
//         pthread_mutex_unlock(&table->locks.death);
//         return true;
//     }
//     pthread_mutex_unlock(&table->locks.death);

//     for (i = 0; i < table->size; ++i) {
//         pthread_mutex_lock(&table->locks.eat);
//         if (table->philosophers[i].action == DEAD || is_dead(&table->philosophers[i])) {
//             pthread_mutex_unlock(&table->locks.eat);
//             return true;
//         }
//         pthread_mutex_unlock(&table->locks.eat);
//     }

//     return false;
// }

bool is_game_over(t_table *table) {
    size_t i = 0;

    pthread_mutex_lock(&table->locks.death);
    if (table->game_over)
	{
        pthread_mutex_unlock(&table->locks.death);
        return true;
    }
    pthread_mutex_unlock(&table->locks.death);

    while (i < table->size || check_death_flag(table->philosophers))
	{
        pthread_mutex_lock(&table->locks.eat);
        if (table->philosophers[i].action == DEAD || is_dead(&table->philosophers[i]))
		{
            pthread_mutex_unlock(&table->locks.eat);
            return true;
        }
        pthread_mutex_unlock(&table->locks.eat);
        i++;
    }

    return false;
}


// bool is_game_over(t_table *table)
// {
// 	size_t	i;

// 	i = 0;
// 	while (i < table->size || check_death_flag(&table->philosophers[i]))
// 	{
// 		if (table->philosophers->action == DEAD || is_dead(&table->philosophers[i]))
// 		{
// 			pthread_mutex_lock(&table->locks.print);
// 			pthread_mutex_lock(&table->locks.death);
// 			table->game_over = true;
// 			pthread_mutex_unlock(&table->locks.print);
// 			pthread_mutex_unlock(&table->locks.death);
// 			return (1);
// 		}
// 		i++;
// 	}
// 	return (false);
// }

// bool	is_game_over(t_philo *philo)
// {
// 	size_t	i;

// 	i = 0;
// 	while (i < philo->table->size || check_death_flag(philo))
// 	{
// 		if (philo[i].action == DEAD || is_dead(&philo[i]))
// 		{
// 			pthread_mutex_lock(&philo->locks->print);
// 			pthread_mutex_lock(&philo->locks->death);
// 			philo->table->game_over = true;
// 			pthread_mutex_unlock(&philo->locks->print);
// 			pthread_mutex_unlock(&philo->locks->death);
// 			return (1);
// 		}
// 		i++;
// 	}
// 	return (0);
// }

// bool is_game_over(const t_table *table)
// {
// 	size_t	i;

// 	i = 0;
// 	while (i < table->size)
// 	{
// 		if (table->philosophers[i].action == DEAD)
// 			return (true);
// 		++i;
// 	}
// 	return (false);
//}

/**
 * Get the current time in milliseconds.
 */
t_time	get_current_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
	{
		perror("Error: gettimeofday");
		exit(EXIT_FAILURE);
	}
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

/*
* Safely sleep for a given duration,
* periodically checking if the philosopher has died.
*/
int ft_safe_usleep(t_time duration, t_philo *philo)
{
	t_time start_time = get_current_time();

	while ((get_current_time() - start_time) < duration)
	{
		if (is_game_over(philo->table)) {
			return 1;
		}
		usleep(500);
	}
	return (0);
}

void destroy_and_free(t_table *table)
{
	pthread_mutex_destroy(&table->locks.eat);
	pthread_mutex_destroy(&table->locks.print);
	pthread_mutex_destroy(&table->locks.death);
	if (table->forks != NULL)
	{
		//TODO: remove for loop 
		for (size_t i = 0; i < table->size; ++i)
		{
			pthread_mutex_destroy(&table->forks[i]);
		}
	}
	if (table->philosophers != NULL)
		free(table->philosophers);
	if (table->forks != NULL)
		free(table->forks);
}

void	*monitoring(void *table_ptr)
{
	t_table	*table;

	table = (t_table *)table_ptr;
	while (1)
	{
		if (is_game_over(table))
		{
			//table->game_over = true;
			break ;
		}
		//usleep(1000);
	}
	pthread_mutex_lock(&table->locks.print);
	table->can_write = false;
	pthread_mutex_unlock(&table->locks.print);
	return (NULL);
}
