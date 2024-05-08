/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vketteni <vketteni@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 19:32:53 by vketteni          #+#    #+#             */
/*   Updated: 2024/05/07 19:32:56 by vketteni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	he_eats(t_thread_data *thread_data)
{
	int				thread_id;
	t_locks			*locks;

	thread_id = thread_data->thread_id;
	locks = thread_data->locks;
	if (thread_data->simulation->philosopher_died_flag)
		return (1);
	pthread_mutex_lock(&locks->mealtime_mutexes[thread_id]);
	thread_data->last_mealtime = get_timestamp();
	philosopher_log("is eating\n", thread_data, &(locks->print_lock));
	pthread_mutex_unlock(&locks->mealtime_mutexes[thread_id]);
	pthread_mutex_lock(&locks->mealtime_mutexes[thread_id]);
	usleep(thread_data->simulation->time_to_eat * 1000);
	thread_data->meal_count++;
	thread_data->last_mealtime = get_timestamp();
	pthread_mutex_unlock(&locks->mealtime_mutexes[thread_id]);
	return (0);
}
