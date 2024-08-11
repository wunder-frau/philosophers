#include "philo.h"

/**
 * Log a philosopher's action with a timestamp.
 */
void	log_action(t_philo *philo, const char *event_message)
{
	t_time	time;
	// if (philo->table->game_over)
	// 	return;

	pthread_mutex_lock(&philo->locks->print);
	time = get_current_time() - philo->intervals.start;
		if (philo->table->can_write == true )
	printf("%zu %zu %s\n", time, philo->id + 1, event_message);
	pthread_mutex_unlock(&philo->locks->print);
}

// void log_action(t_philo *philo, const char *event_message)
// {
//     t_time time;
    
//     // Locking the mutex to ensure thread-safe logging
//     pthread_mutex_lock(&philo->locks->print);
    
//     // Only log if the game is not over
//     if (!philo->table->game_over) 
//     {
//         time = get_current_time() - philo->intervals.start;
//         printf("%zu %zu %s\n", time, philo->id + 1, event_message);
//     }
    
//     // Unlock the mutex after logging
//     pthread_mutex_unlock(&philo->locks->print);
// }

