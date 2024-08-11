#ifndef PHILO_H
#define PHILO_H

#include <pthread.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <unistd.h>

typedef struct s_table t_table;

//: Time {{{
typedef long t_time;
// typedef struct timeval	t_time;

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
	pthread_mutex_t	death;
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
	t_intervals		intervals;
	t_time			last_meal_time;
	t_table			*table;
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
	bool	game_over;
} t_table;
//: }}}

// typedef struct s_act_args
// {
// 	t_table *table;
// 	t_philo	*philo;
// } t_act_args;

t_table allocate(const t_intervals, size_t);
void assign(t_table *);
t_philo *allocate_philos(const size_t, t_locks *, t_intervals );
void init(t_table *);
// bool	init_mutex_array(int count, pthread_mutex_t **mutex);

/* utils.c */
bool 	is_dead(t_philo *);
t_time	get_current_time(void);
int		ft_safe_usleep(t_time , t_philo *);
void	destroy_and_free(t_table *table);
void 	*monitoring(void *table_ptr);
bool 	is_game_over(const t_table *);

/* log_action.c */
void	log_action(t_philo *philo, const char *event_message);

/* actions.c */
void	*act(void *);
void	destroy(pthread_mutex_t **mutexes, size_t n);

#endif