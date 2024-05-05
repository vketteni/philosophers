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

int	philosophers(t_locks *locks, t_data *data)
{
	long			i;
	t_thread_data	*thread_data;
	pthread_t		*threads;
	unsigned long	starttime;

	if (!locks || !data)
		return (EXIT_FAILURE);
	threads = initialize_threads(data->num_philosophers);
	if (!threads)
		return (free_memory(locks, NULL, data));
	thread_data = initialize_thread_data(threads, locks, data);
	if (!thread_data)
		return (free_memory(locks, NULL, data));
	// pthread_mutex_lock(&(locks->print_lock));
	// printf("Number of philosophers: %d\n", data->num_philosophers);
	// pthread_mutex_unlock(&(locks->print_lock));
	i = 0;
	while (i < data->num_philosophers)
	{
		// pthread_mutex_lock(&(locks->thread_mutexes[2]));
		// printf("Create thread %zu\n", i + 1);
		// pthread_mutex_unlock(&(locks->thread_mutexes[2]));
		pthread_create(&(threads[i]), NULL, thread_routine,
			(void *)&(thread_data[i]));
		i++;
	}
	locks->starttime_flag = 1;
	starttime = get_timestamp();
	philosopher_log("start\n", &(thread_data[0]), &locks->print_lock);
	usleep(200);
	i = 0;
	while (1)
	{
		unsigned long	time = get_timestamp() - thread_data[i].mealtime;
		if (time >= (unsigned long)data->time_to_die)
		{
			pthread_mutex_lock(&locks->print_lock);
			printf(" %ld >= %ld \n", time, (unsigned long)data->time_to_die);
			pthread_mutex_unlock(&locks->print_lock);
			philosopher_log("died\n", &thread_data[i], &locks->print_lock);
			thread_data[i].locks->philosopher_died_flag = 1;
			break ;
		}
		i = (i + 1) % data->num_philosophers;
	}
	while (i < data->num_philosophers)
	{
		// pthread_mutex_lock(&(locks->print_lock));
		// printf("Trying to end %ld \n", i + 1);
		// pthread_mutex_unlock(&(locks->print_lock));
		pthread_join(thread_data[i].thread, NULL);
		// pthread_mutex_lock(&(locks->print_lock));
		// printf("Thread %ld ended\n", i + 1);
		// pthread_mutex_unlock(&(locks->print_lock));
		i++;
	}
	pthread_mutex_lock(&(locks->print_lock));
	printf("All threads completed.\n");
	pthread_mutex_unlock(&(locks->print_lock));
	return (EXIT_SUCCESS);
}

int	main(int argc, const char **argv)
{
	t_locks	*locks;
	t_data	*data;

	if (check_arguments(argc, argv))
		return (EXIT_FAILURE);
	data = initialize_input(argc, argv);
	if (!data)
		return (free_memory(NULL, NULL, NULL));
	locks = create_locks(data);
	if (!locks)
		return (EXIT_FAILURE);
	if (philosophers(locks, data))
		return (free_memory(locks, NULL, data));
	free_memory(locks, NULL, NULL);
	return (EXIT_SUCCESS);
}
