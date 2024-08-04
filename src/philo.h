#ifndef PHILO_H
#define PHILO_H

#include <pthread.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <unistd.h>

//: Time {{{
typedef size_t t_time;
// typedef struct timeval	t_time;

typedef struct s_intervals
{
	t_time	die;
	t_time	eat;
	t_time	sleep;
	// t_time	timestamp;
} t_intervals;

typedef struct s_locks
{
	pthread_mutex_t	print;
	pthread_mutex_t	eat;
	// pthread_mutex_t	dead;
} t_locks;
//: }}}

//: Philosopher {{{
typedef enum e_action
{
	EAT,
	SLEEP,
	THINK,
	DEAD
} t_action;

typedef struct s_philo
{
	size_t			id;
	t_action		action;
	pthread_t		thread;
	pthread_mutex_t	state;
	pthread_mutex_t	*left;
	pthread_mutex_t	*right;
	t_locks			*locks;
} t_philo;
//: }}}

//: Philosophical room {{{
// typedef pthread_mutex_t	t_fork;

typedef struct s_table
{
	size_t	size; // there are as many forks as philosophers
	pthread_mutex_t	*forks;
	t_philo	*philosophers;
	t_locks	locks;
	t_intervals	intervals;
} t_table;
//: }}}

t_table allocate(const t_intervals, size_t);
void assign(t_table *);
void init(t_table *);

// long get_current_timestamp(void);
// bool	init_mutex_array(int count, pthread_mutex_t **mutex);

#endif