#ifndef PHILO_H
#define PHILO_H

#include <pthread.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

//: Time {{{
typedef size_t t_time; //FIXME: 2. has pthread.h its own defined time type? Smth. like pthread_time_t?

typedef struct s_intervals
{
	t_time	die;
	t_time	eat;
	t_time	sleep;
	t_time	timestamp;
} t_intervals;
//: }}}

//: Philosopher {{{
typedef enum e_state
{
	EATING,
	SLEEPING,
	THINKING,
	DEAD
} t_state;

typedef struct s_philosopher
{
	size_t			id;
	t_state			state;
	t_intervals		intervals;
	pthread_mutex_t	*left;
	pthread_mutex_t	*right;
} t_philosopher;
//: }}}

//: Philosophical room {{{
// typedef pthread_mutex_t	t_fork;

typedef struct s_table
{
	t_philosopher	*philosophers;
	pthread_mutex_t	*forks;
	size_t			size; // there are as many forks as philosophers
} t_table;

t_table allocate(const t_intervals, size_t);
void assign(t_table *table);
long get_current_timestamp(void);
//: }}}

#endif