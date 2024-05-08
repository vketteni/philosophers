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

#include "../philo.h"

void	pick_left_fork(t_thread_data *thread_data)
{
	int		thread_id;
	t_locks	*locks;

	thread_id = thread_data->thread_id;
	locks = thread_data->locks;
	pthread_mutex_lock(&(locks->thread_mutexes[thread_id]));
}

void	pick_right_fork(t_thread_data *thread_data)
{
	int		thread_id;
	t_locks	*locks;
	int		num_philosophers;

	thread_id = thread_data->thread_id;
	num_philosophers = thread_data->simulation->num_philosophers;
	locks = thread_data->locks;
	pthread_mutex_lock(&(locks->thread_mutexes[(thread_id + 1)
			% (num_philosophers)]));
}

int	he_picks_up_forks(t_thread_data *thread_data)
{
	int		thread_id;
	t_locks	*locks;

	thread_id = thread_data->thread_id;
	locks = thread_data->locks;
	if (thread_data->simulation->philosopher_died_flag)
		return (1);
	pick_left_fork(thread_data);
	philosopher_log("has taken the left fork\n", thread_data,
		&(locks->print_lock));
	while (thread_data->simulation->num_philosophers == 1)
	{
		if (thread_data->simulation->philosopher_died_flag)
			return (1);
		usleep(10000);
	}
	pick_right_fork(thread_data);
	philosopher_log("has taken the right fork\n", thread_data,
		&(locks->print_lock));


	return (0);
}
