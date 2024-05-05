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

t_data	*initialize_input(int argc, const char **argv)
{
	t_data			*data;

	data = (t_data *)malloc(sizeof(t_data));
	if (!data)
		return (NULL);
	data->num_philosophers = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		data->num_must_eat = ft_atoi(argv[5]);
	return (data);
}

t_thread_data	*initialize_thread_data(pthread_t *threads, t_locks *locks, t_data *data)
{
	t_thread_data	*thread_data;
	int	i;

	if (!data || !locks)
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
		thread_data[i].mealtime = 0;
		thread_data[i].locks = locks;
		thread_data[i].input_data = data;
		i++;
	}
	return (thread_data);
}