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
	threads = (pthread_t *)malloc(sizeof(pthread_t) * num_threads);
	if (!threads)
		return (NULL);
	memset(threads, 0, num_threads);
	return (threads);
}

t_simulation	*initialize_simulation(int argc, const char **argv)
{
	t_simulation	*simulation;

	simulation = (t_simulation *)malloc(sizeof(t_simulation));
	if (!simulation)
		return (NULL);
	memset(simulation, 0, sizeof(t_simulation));
	simulation->num_philosophers = ft_atoi(argv[1]);
	simulation->time_to_die = ft_atoi(argv[2]);
	simulation->time_to_eat = ft_atoi(argv[3]);
	simulation->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		simulation->num_must_eat = ft_atoi(argv[5]);
	simulation->philosopher_died_flag = 0;
	simulation->starttime = 0;
	return (simulation);
}

t_thread_data	*initialize_threads_data(pthread_t *threads, t_locks *locks,
		t_simulation *simulation)
{
	t_thread_data	*thread_data;
	unsigned long	i;

	if (!simulation || !locks)
		return (NULL);
	thread_data = (t_thread_data *)malloc(sizeof(t_thread_data)
			* simulation->num_philosophers);
	if (!thread_data)
		return (NULL);
	i = 0;
	while (i < simulation->num_philosophers)
	{
		thread_data[i].thread = threads[i];
		thread_data[i].thread_id = i;
		thread_data[i].last_mealtime = 0;
		thread_data[i].locks = locks;
		thread_data[i].meal_count = 0;
		thread_data[i].total_meals = false;
		thread_data[i].simulation = simulation;
		i++;
	}
	return (thread_data);
}
