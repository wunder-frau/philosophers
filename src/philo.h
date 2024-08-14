#ifndef PHILO_H
#define PHILO_H

#include <pthread.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
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
	long			meal_count;
	long			last_meal_time;
	pthread_mutex_t	*mtx_philo;
	t_table			*table;
} t_philo;

typedef struct s_table
{
	size_t	size; // there are as many forks as philosophers
	t_time	die;
	t_time	eat;
	t_time	sleep;
	long	meal_count;
	size_t	satiation_count;
	t_time	action_gap;
	t_time	init_time;
	long	game_over;
	t_philo	*philosophers;
	pthread_mutex_t	*mtx_philosophers;
	pthread_mutex_t	*mtx_forks;
	pthread_mutex_t	*mtx_act;
	pthread_t		*monitor;
	pthread_t		*threads;
} t_table;
//: }}}

bool	is_args_valid(int argc, char **argv, t_table *table);

bool	allocate(t_table *table);
void	assign(t_table *);
bool	allocate_philosophers(t_table *table, size_t size);
bool	allocate_threads(t_table *table);
bool		init(t_table *);
// bool	init_mutex_array(int count, pthread_mutex_t **mutex);

/* utils.c */
long	get_current_time(void);
void	ft_usleep(int msec, t_table *table);
void	destroy_and_free(t_table *table);

/* log_action.c */
bool	log_action(t_philo *philo, t_time timestamp, char *act_msg);

/* actions.c */
void	*act(void *philo_ptr);
bool	allocate_mutexes(pthread_mutex_t **mutexes, size_t size);
void	destroy(pthread_mutex_t *mutexes, size_t n);

void	atomic_set(pthread_mutex_t *mutex, long *variable, long value);
long	atomic_get(pthread_mutex_t *mutex, long *variable);


/* initialization_time.c */
void	set_init_time(t_table *table, size_t i);
int		wait_for_init_time_is_set(t_philo *philo);

/* time_managment_utils.c */
int		calculate_action_gap(t_time die, t_time eat, t_time sleep);

void	*monitoring(void *arg);
#endif