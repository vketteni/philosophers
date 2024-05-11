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

#include "philo_bonus.h"

// void	initialize_last_mealtime(t_locks *locks, long thread_id,
// 		t_thread_data *thread_data)
// {
// 	pthread_mutex_t	*mealtime_lock;

// 	mealtime_lock = &locks->mealtime_mutexes[thread_id];
// 	pthread_mutex_lock(mealtime_lock);
// 	thread_data->last_mealtime = get_timestamp();
// 	pthread_mutex_unlock(mealtime_lock);
// }

void	*philo_process(void *arg)
{
	t_data	*data;

	data = (t_data *)arg;
	// initialize_last_mealtime(thread_data->locks, thread_data->thread_id,
	// 	thread_data);
	if (data->id % 2 == 0)
		usleep(data->simulation->time_to_eat * 1000);
	while (1)
	{
		if (he_picks_up_forks(data) || he_eats(data)
			|| he_releases_forks(data) || he_sleeps(data)
			|| he_thinks(data))
			break ;
	}
	return (NULL);
}
