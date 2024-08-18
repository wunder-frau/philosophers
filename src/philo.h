/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: istasheu <istasheu@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 02:14:42 by istasheu          #+#    #+#             */
/*   Updated: 2024/08/19 02:14:44 by istasheu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdbool.h>
# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

typedef long			t_time;
typedef struct s_table	t_table;

typedef struct s_philo
{
	size_t			id;
	pthread_mutex_t	*forks[2];
	long			meal_count;
	long			last_meal_time;
	t_table			*table;
}	t_philo;

typedef struct s_timing
{
	t_time	die;
	t_time	eat;
	t_time	sleep;
	t_time	start;
	t_time	action_gap;
}	t_timing;

typedef struct s_table
{
	size_t			size;
	t_timing		timing;
	long			meal_count;
	size_t			satiation_count;
	bool			is_game_over;
	t_philo			*philosophers;
	pthread_mutex_t	*mtx_forks;
	pthread_mutex_t	*mtx_act;
	pthread_t		*monitor;
	pthread_t		*threads;
}	t_table;

typedef struct s_actions
{
	const char	*taken_fork;
	const char	*died;
	const char	*sleeping;
	const char	*eating;
	const char	*thinking;
}	t_actions;

/* actions.c */
void		*act(void *philo_ptr);

/* assign.c */
bool		allocate_philosophers(t_table *table, size_t size);
bool		allocate_threads(t_table *table);
bool		allocate(t_table *table);

/* atomics.c */
long		atomic_get(pthread_mutex_t *mutex, long *variable);
void		atomic_set(pthread_mutex_t *mutex, long *variable, long value);

/* destroy_and_free.c */
void		destroy_and_free(t_table *table);

/* init.c */
bool		init(t_table *table);

/* log_action.c */
bool		log_action(t_philo *philo, long time, const char *act_msg);

/* monitor */
void		*monitoring(void *table_ptr);

/* timing */
long		get_curr_time(void);
void		ft_usleep(int msec, t_table *table);
void		set_action_gap(t_timing *t);
void		set_start_time(t_table *table, size_t i);
int			wait_for_init_time_is_set(t_philo *philo);

/* utils_actions.c */
t_actions	create_actions(void);
void		wait_for_appropriate_time(t_philo *philo);

/* utils_mtx.c */
void		swap(pthread_mutex_t *a, pthread_mutex_t *b);
void		destroy(pthread_mutex_t *mutexes, size_t n);
bool		allocate_mutexes(pthread_mutex_t **mutexes, size_t size);

/* utils.c */
int			ft_isdigit(int d);
int			ft_is_space(char c);
void		ft_putstr_fd(char *s, int fd);
long		ft_atol(char *str);
void		*ft_calloc(size_t count, size_t size);

/* validation.c */
bool		parse_and_assign_args(int argc, char **argv, t_table *table);

#endif