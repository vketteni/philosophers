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

#include "../philo_bonus.h"

int	he_eats(t_data *data)
{
	int				id;
	t_locks			*locks;

	id = data->id;
	locks = data->locks;
	if (data->simulation->philosopher_died_flag)
		return (1);
	sem_wait(&locks->mealtime_lock[id]);
	data->last_mealtime = get_timestamp();
	philosopher_log("is eating\n", data, &(locks->print_lock));
	sem_post(&locks->mealtime_lock[id]);
	sem_wait(&locks->mealtime_lock[id]);
	usleep(data->simulation->time_to_eat * 1000);
	data->meal_count++;
	data->last_mealtime = get_timestamp();
	sem_post(&locks->mealtime_lock[id]);
	return (0);
}
