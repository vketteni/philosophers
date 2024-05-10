/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   take_forks.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vketteni <vketteni@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 19:33:14 by vketteni          #+#    #+#             */
/*   Updated: 2024/05/07 19:33:16 by vketteni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo_bonus.h"

int	just_a_single_philosopher(t_thread_data *thread_data)
{
	while (thread_data->simulation->num_philosophers == 1)
	{
		if (thread_data->simulation->philosopher_died_flag)
			return (1);
		usleep(10000);
	}
	return (0);
}

void	pick_left_fork(t_thread_data *thread_data)
{
	int		thread_id;

	thread_id = thread_data->thread_id;
}

void	pick_right_fork(t_thread_data *thread_data)
{
	int		thread_id;
	int		num_philosophers;

	thread_id = thread_data->thread_id;
	num_philosophers = thread_data->simulation->num_philosophers;
}

int	he_picks_up_forks(t_thread_data *thread_data)
{
	int		thread_id;

	thread_id = thread_data->thread_id;
	if (thread_data->simulation->philosopher_died_flag)
		return (1);
	pick_left_fork(thread_data);
	if (just_a_single_philosopher(thread_data))
		return (1);
	pick_right_fork(thread_data);
	return (0);
}
