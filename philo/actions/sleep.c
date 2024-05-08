/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sleep.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vketteni <vketteni@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 19:33:28 by vketteni          #+#    #+#             */
/*   Updated: 2024/05/07 19:33:30 by vketteni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	he_sleeps(t_thread_data *thread_data)
{
	int		thread_id;
	t_locks	*locks;

	thread_id = thread_data->thread_id;
	locks = thread_data->locks;
	if (locks->philosopher_died_flag)
		return (1);
	philosopher_log("is sleeping\n", thread_data, &(locks->print_lock));
	usleep(thread_data->simulation->time_to_sleep * 1000);
	return (0);
}
