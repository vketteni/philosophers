/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initializers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vketteni <vketteni@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 13:57:33 by vketteni          #+#    #+#             */
/*   Updated: 2024/05/01 13:57:35 by vketteni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

pthread_t	*initialize_threads(size_t num_threads)
{
	pthread_t	*threads;

	if (num_threads <= 0)
		return (NULL);
	threads = (pthread_t *)malloc(sizeof(pthread_t) * num_threads + 1);
	if (!threads)
		return (NULL);
	memset(threads, 0, num_threads + 1);
	return (threads);
}

t_data	*initialize_data(int argc, const char **argv)
{
	struct timeval	tv;
	t_data			*data;

	data = (t_data *)malloc(sizeof(t_data));
	if (!data)
		return (NULL);
	gettimeofday(&tv, NULL);
	data->num_philosophers = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		data->num_must_eat = ft_atoi(argv[5]);
	return (data);
}

pthread_mutex_t	*initialize_forks(t_data *data)
{
	int			i;
	pthread_mutex_t	*forks;

	if (!data)
		return (NULL);
	forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * data->num_philosophers);
	if (!forks)
		return (NULL);
	i = 0;
	while (i < data->num_philosophers)
	{
		if (pthread_mutex_init(&(forks[i]), NULL))
		{
			free(forks);
			return (NULL);
		}
		i++;
	}
	return (forks);
}

t_locks	*initialize_mutexes(t_data *data)
{
	t_locks *mutexes;

	if (!data)
		return (NULL);
	mutexes = (t_locks *)malloc(sizeof(t_locks));
	if (!mutexes)
		return (NULL);
	mutexes->thread_mutexes = initialize_forks(data);
	if (!mutexes->thread_mutexes)
	{
		free_memory(mutexes, NULL, NULL);
		return (NULL);
	}
	if (pthread_mutex_init(&(mutexes->print_lock), NULL)
		|| pthread_mutex_init(&(mutexes->total_meals_lock), NULL))
	{
		free_memory(mutexes, NULL, NULL);
		return (NULL);
	}
	return (mutexes);
}

t_thread_data	*initialize_thread_data(t_locks *locks, t_data *data)
{
	pthread_t		*threads;
	t_thread_data	*thread_data;
	int	i;

	if (!data || !locks)
		return (NULL);
	threads = initialize_threads(data->num_philosophers);
	if (!threads)
		return (NULL);
	thread_data = (t_thread_data *)malloc(sizeof(t_thread_data) * data->num_philosophers);
	if (!thread_data)
	{
		free(threads);
		return (NULL);
	}
	i = 0;
	while (i < data->num_philosophers)
	{
		thread_data[i].thread = threads[i];
		thread_data[i].thread_id = i;
		thread_data[i].starttime = 0;
		thread_data[i].thread_lock = &(locks->thread_mutexes[i]);
		thread_data[i].last_meal_lock = &(locks->last_meal_lock);
		thread_data[i].print_lock = &(locks->print_lock);
		thread_data[i].total_meals_lock = &(locks->print_lock);

		i++;
	}
	return (thread_data);
}