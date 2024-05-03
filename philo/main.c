/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vketteni <vketteni@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 11:11:44 by vketteni          #+#    #+#             */
/*   Updated: 2024/04/29 11:11:46 by vketteni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

	// printf("Hi philosopher %ld\n", thread_data->thread_id);
	// gettimeofday(&tv, NULL);
	// printf("Timestamp %d\n", (long)(tv.tv_sec * 1000 + tv.tv_usec / 1000));
	// usleep(1000);

void	picks_up_forks(t_thread_data *thread_data)
{
	int	thread_id;
	int	num_philosophers;
	struct timeval	tv;

	thread_id = thread_data->thread_id;
	num_philosophers = thread_data->data.num_philosophers;
	pthread_mutex_lock((thread_data[thread_id].thread_lock));
	pthread_mutex_lock((thread_data[thread_id].print_lock));
	gettimeofday(&tv, NULL);
	printf("%ld %d has taken a fork\n", (long)(tv.tv_sec * 1000 + tv.tv_usec / 1000), thread_id + 1);
	pthread_mutex_unlock((thread_data[thread_id].print_lock));

	pthread_mutex_lock((thread_data[(thread_id + 1) % (num_philosophers)].thread_lock));
	pthread_mutex_lock((thread_data[thread_id].print_lock));
	gettimeofday(&tv, NULL);
	printf("%ld %d has taken a fork\n", (long)(tv.tv_sec * 1000 + tv.tv_usec / 1000), thread_id + 1);
	pthread_mutex_unlock((thread_data[thread_id].print_lock));
}

void	eats(t_thread_data *thread_data)
{
	int	thread_id;
	int	num_philosophers;
	struct timeval	tv;

	thread_id = thread_data->thread_id;
	num_philosophers = thread_data->data.num_philosophers;

	pthread_mutex_lock((thread_data[thread_id].print_lock));
	gettimeofday(&tv, NULL);
	printf("%ld %d is eating\n", (long)(tv.tv_sec * 1000 + tv.tv_usec / 1000), thread_id + 1);
	pthread_mutex_unlock((thread_data[thread_id].print_lock));

	usleep(thread_data[thread_id].data.time_to_eat * 1000);

	pthread_mutex_lock((thread_data[thread_id].last_meal_lock));
	gettimeofday(&tv, NULL);
	thread_data[thread_id].starttime = tv.tv_sec * 1000 + tv.tv_usec / 1000;
	pthread_mutex_unlock((thread_data[thread_id].last_meal_lock));
}

void	puts_down_forks(t_thread_data *thread_data)
{
	int	thread_id;
	int	num_philosophers;

	thread_id = thread_data->thread_id;
	num_philosophers = thread_data->data.num_philosophers;

	pthread_mutex_unlock((thread_data[thread_id].thread_lock));
	pthread_mutex_unlock((thread_data[(thread_id + 1) % (num_philosophers)].thread_lock));
}

void	sleeps(t_thread_data *thread_data)
{
	int	thread_id;
	int	num_philosophers;
	struct timeval	tv;

	thread_id = thread_data->thread_id;
	num_philosophers = thread_data->data.num_philosophers;
	pthread_mutex_lock((thread_data[thread_id].print_lock));
	gettimeofday(&tv, NULL);
	printf("%ld %d is sleeping\n", (long)(tv.tv_sec * 1000 + tv.tv_usec / 1000), thread_id + 1);
	pthread_mutex_unlock((thread_data[thread_id].print_lock));
	usleep(thread_data[thread_id].data.time_to_sleep * 1000);
}

void	thinks(t_thread_data *thread_data)
{
	int	thread_id;
	int	num_philosophers;
	struct timeval	tv;

	thread_id = thread_data->thread_id;
	num_philosophers = thread_data->data.num_philosophers;
	pthread_mutex_lock((thread_data[thread_id].print_lock));
	gettimeofday(&tv, NULL);
	printf("%ld %d is thinking\n", (long)(tv.tv_sec * 1000 + tv.tv_usec / 1000), thread_id + 1);
	pthread_mutex_unlock(thread_data[thread_id].print_lock);
}

void	*thread_routine(void *arg)
{
	t_thread_data	*thread_data;

	thread_data = (t_thread_data *)arg;
	while (1)
	{
		picks_up_forks(thread_data);
		eats(thread_data);
		puts_down_forks(thread_data);
		sleeps(thread_data);
		thinks(thread_data);
	}
	return (NULL);
}


int	philosophers(t_locks *locks, t_data *data)
{
	long			i;
	t_thread_data	*thread_data;

	if (!locks || !data)
		return (EXIT_FAILURE);
	thread_data = initialize_thread_data(locks, data);
	if (!thread_data)
		return (free_memory(locks, NULL, data));
	pthread_mutex_lock(&(locks->print_lock));
	printf("Number of philosophers: %d\n", data->num_philosophers);
	pthread_mutex_unlock(&(locks->print_lock));
	i = 0;
	while (i < data->num_philosophers)
	{
		pthread_mutex_lock(&(locks->print_lock));
		printf("Create thread %ld\n", i + 1);
		pthread_mutex_unlock(&(locks->print_lock));
		pthread_create(&(thread_data[i].thread), NULL, thread_routine, (void *)&(thread_data[i]));
		i++;		
	}

	i = 0;
	while (i < data->num_philosophers)
	{
		pthread_join(thread_data[i].thread, NULL);
		pthread_mutex_lock(&(locks->print_lock));
		printf("Thread %ld ended\n", i + 1);
		pthread_mutex_unlock(&(locks->print_lock));
		i++;
	}
	pthread_mutex_lock(&(locks->print_lock));
	printf("All threads completed.\n");
	pthread_mutex_unlock(&(locks->print_lock));
	return (EXIT_SUCCESS);
}

int	main(int argc, const char **argv)
{
	t_locks		*mutexes;
	t_data		*data;

	if (check_arguments(argc, argv))
		return (EXIT_FAILURE);
	data = initialize_data(argc, argv);
	if (!data)
		return (free_memory(NULL, NULL, NULL));
	mutexes = initialize_mutexes(data);
	if (!mutexes)
		return (EXIT_FAILURE);
	if (philosophers(mutexes, data))
		return (free_memory(mutexes, NULL, data));
	free_memory(mutexes, NULL, NULL);
	return (EXIT_SUCCESS);
}
