/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_locks.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vketteni <vketteni@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 19:34:13 by vketteni          #+#    #+#             */
/*   Updated: 2024/05/07 19:34:14 by vketteni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_locks	*initialize_locks(t_locks *locks, t_simulation *data)
{
	unsigned long	i;

	if (!data)
		return (NULL);
	i = 0;
	while (i < data->num_philosophers)
	{
		if (pthread_mutex_init(&(locks->thread_mutexes[i]), NULL)
			|| pthread_mutex_init(&(locks->mealtime_locks[i]), NULL))
			return (NULL);
		i++;
	}
	if (pthread_mutex_init(&(locks->print_lock), NULL))
		return (NULL);
	return (locks);
}

t_locks	*create_locks(t_simulation *data)
{
	t_locks	*mutexes;

	if (!data)
		return (NULL);
	mutexes = (t_locks *)malloc(sizeof(t_locks));
	if (!mutexes)
		return (NULL);
	mutexes->thread_mutexes = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t)
			* data->num_philosophers);
	if (!mutexes->thread_mutexes)
		return (NULL);
	mutexes->mealtime_locks = 
		(pthread_mutex_t *)malloc(sizeof(pthread_mutex_t)
			* data->num_philosophers);
	if (!mutexes->mealtime_locks)
	{
		free_memory(mutexes, NULL, NULL);
		return (NULL);
	}
	if (!initialize_locks(mutexes, data))
	{
		free_memory(mutexes, NULL, NULL);
		return (NULL);
	}
	return (mutexes);
}
