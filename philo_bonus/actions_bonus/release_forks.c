/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   release_forks.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vketteni <vketteni@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 19:33:42 by vketteni          #+#    #+#             */
/*   Updated: 2024/05/07 19:33:44 by vketteni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	release_left_fork(t_thread_data *thread_data)
{
	int		thread_id;
	int		num_philosophers;
	t_locks	*locks;

	thread_id = thread_data->thread_id;
	num_philosophers = thread_data->simulation->num_philosophers;
	locks = thread_data->locks;
	philosopher_log("has released left fork\n", thread_data,
		&(locks->print_lock));
	pthread_mutex_unlock(&(locks->thread_mutexes[thread_id]));
}

void	release_right_fork(t_thread_data *thread_data)
{
	int		thread_id;
	int		num_philosophers;
	t_locks	*locks;

	thread_id = thread_data->thread_id;
	num_philosophers = thread_data->simulation->num_philosophers;
	locks = thread_data->locks;
	philosopher_log("has released right fork\n", thread_data,
		&(locks->print_lock));
	pthread_mutex_unlock(&(locks->thread_mutexes[(thread_id + 1)
			% (num_philosophers)]));
}

int	he_releases_forks(t_thread_data *thread_data)
{
	int		thread_id;
	int		num_philosophers;
	t_locks	*locks;

	thread_id = thread_data->thread_id;
	num_philosophers = thread_data->simulation->num_philosophers;
	locks = thread_data->locks;
	if (thread_data->simulation->philosopher_died_flag)
		return (1);
	release_left_fork(thread_data);
	release_right_fork(thread_data);
	return (0);
}
