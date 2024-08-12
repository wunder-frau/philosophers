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

typedef struct s_intervals
{
	t_time	die;
	t_time	eat;
	t_time	sleep;
	t_time	start;
	// t_time	timestamp;
} t_intervals;

typedef struct s_locks
{
	pthread_mutex_t	print;
	pthread_mutex_t	eat;
	pthread_mutex_t	dead;
} t_locks;


//: Philosopher {{{
typedef enum e_action
{
	EAT,
	SLEEP,
	THINK,
	DEAD
} t_action;

//: Philosophical room {{{
typedef struct s_philo
{
	size_t			id;
	pthread_mutex_t	*left;
	pthread_mutex_t	*right;
	long			last_meal_time;
	pthread_mutex_t	*philo;
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
	pthread_mutex_t	*philo;
	pthread_mutex_t	*forks;
	pthread_mutex_t	*death;
	pthread_t		*monitor;
	pthread_t		*threads;
} t_table;
//: }}}

t_table allocate(const t_intervals, size_t);
void assign(t_table *);
t_philo *allocate_philos(const size_t size, t_locks *locks, t_intervals intervals);
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
void	destroy(pthread_mutex_t **mutexes, size_t n);

#endif