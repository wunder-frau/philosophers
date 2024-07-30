#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>

typedef struct s_philosopher
{
	int id;
	int left_fork;
	int right_fork;
	pthread_mutex_t *forks;
	pthread_mutex_t *write_lock;
} t_philosopher;


void *philosopher_routine(void *arg)
{
	t_philosopher *philosopher = (t_philosopher *)arg;
	pthread_mutex_lock(philosopher->write_lock);
	printf("Philosopher %d initialized\n", philosopher->id);
	pthread_mutex_unlock(philosopher->write_lock);
	return NULL;
}

int main(int argc, char **argv)
{
	if (argc != 5)
	{
		fprintf(stderr, "Usage: %s number_of_philosophers time_to_die time_to_eat time_to_sleep\n", argv[0]);
		return 1;
	}

	int number_of_philosophers = atoi(argv[1]);

	pthread_mutex_t *forks = malloc(number_of_philosophers * sizeof(pthread_mutex_t));
	pthread_t *threads = malloc(number_of_philosophers * sizeof(pthread_t));
	t_philosopher *philosophers = malloc(number_of_philosophers * sizeof(t_philosopher));
	pthread_mutex_t write_lock;

	pthread_mutex_init(&write_lock, NULL);
	for (int i = 0; i < number_of_philosophers; i++)
		pthread_mutex_init(&forks[i], NULL);

	for (int i = 0; i < number_of_philosophers; i++)
	{
		philosophers[i].id = i + 1;
		philosophers[i].left_fork = i;
		philosophers[i].right_fork = (i + 1) % number_of_philosophers;
		philosophers[i].forks = forks;
		philosophers[i].write_lock = &write_lock;

		if (pthread_create(&threads[i], NULL, philosopher_routine, &philosophers[i]) != 0)
		{
			perror("Failed to create thread");
			return 1;
		}
	}
	for (int i = 0; i < number_of_philosophers; i++)
		pthread_join(threads[i], NULL);
	for (int i = 0; i < number_of_philosophers; i++) 
			pthread_mutex_destroy(&forks[i]);
	pthread_mutex_destroy(&write_lock);
	free(forks);
	free(threads);
	free(philosophers);
	return 0;
}
