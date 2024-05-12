/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_routine.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vketteni <vketteni@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 19:38:14 by vketteni          #+#    #+#             */
/*   Updated: 2024/05/07 19:38:15 by vketteni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	initialize_last_mealtime(t_locks *locks, t_thread_data *thread_data)
{
	pthread_mutex_t	*mealtime_lock;
	long			thread_id;

	thread_id = thread_data->thread_id;
	mealtime_lock = &locks->mealtime_locks[thread_id];
	pthread_mutex_lock(mealtime_lock);
	thread_data->last_mealtime = get_timestamp();
	pthread_mutex_unlock(mealtime_lock);
}

int	philosopher_full(t_thread_data *thread_data, t_simulation *simulation)
{
	unsigned long	meal_count;
	unsigned long	thread_id;

	thread_id = thread_data->thread_id;
	pthread_mutex_lock(&thread_data->locks->mealtime_locks[thread_id]);
	meal_count = thread_data->meal_count;
	pthread_mutex_unlock(&thread_data->locks->mealtime_locks[thread_id]);
	if (simulation->num_must_eat > 0
		&& meal_count == simulation->num_must_eat)
		return (1);
	return (0);
}

void	*thread_routine(void *arg)
{
	t_thread_data	*thread_data;
	t_simulation	*simulation;
	t_locks			*locks;

	thread_data = (t_thread_data *)arg;
	simulation = thread_data->simulation;
	locks = thread_data->locks;
	initialize_last_mealtime(locks, thread_data);
	if (thread_data->thread_id % 2 == 0)
		usleep(simulation->time_to_eat * 1000);
	while (1)
	{
		if (philosopher_full(thread_data, simulation))
			break ;
		if (simulation->philosopher_died_flag)
			break ;
		if (he_picks_up_forks(thread_data) || he_eats(thread_data)
			|| he_releases_forks(thread_data) || he_sleeps(thread_data)
			|| he_thinks(thread_data))
			break ;
	}
	return (NULL);
}
