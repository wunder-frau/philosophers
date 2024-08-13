#ifndef PHILO_H
#define PHILO_H

#include <pthread.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <unistd.h>
#include "../libft_/libft.h"

//: Time {{{
typedef long t_time;
//: }}}
typedef struct s_table t_table;

//: Philosophical room {{{
typedef struct s_philo
{
	size_t			id;
	pthread_mutex_t	*mtx_left;
	pthread_mutex_t	*mtx_right;
	long			last_meal_time;
	pthread_mutex_t	*mtx_philo;
	t_table			*table;
} t_philo;

typedef struct s_table
{
	long	size; // there are as many forks as philosophers
	t_time	die;
	t_time	eat;
	t_time	sleep;
	long	n_meals;
	long	n_full;
	t_time	t_wait;
	t_time	start;
	long	finished;
	t_philo	*philosophers;
	pthread_mutex_t	*mtx_philo;
	pthread_mutex_t	*mtx_forks;
	pthread_mutex_t	*mtx_death;
	pthread_t		*monitor;
	pthread_t		*threads;
} t_table;
//: }}}

bool	is_args_valid(int argc, char **argv, t_table *table);

bool	allocate(t_table *table);
void	assign(t_table *);
bool	allocate_philos(t_table *table, long size);
void init(t_table *);
// bool	init_mutex_array(int count, pthread_mutex_t **mutex);
bool is_dead(t_philo *philo);

/* utils.c */
long	get_current_time(void);
int		ft_safe_usleep(t_time duration, t_philo *philo);
void	destroy_and_free(t_table *table);

/* log_action.c */
void log_action(t_philo *philo, const char *event_message);

/* actions.c */
void	*act(void *philo_ptr);
bool	allocate_mutexes(pthread_mutex_t **mutexes, long size);
void	destroy(pthread_mutex_t *mutexes, size_t n);

#endif