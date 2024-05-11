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

#include "../philo_bonus.h"

void	release_left_fork(t_data *data)
{
	int		id;
	int		num_philosophers;
	t_locks	*locks;

	id = data->id;
	num_philosophers = data->simulation->num_philosophers;
	locks = data->locks;
	philosopher_log("has released left fork\n", data,
		&(locks->print_lock));
	sem_post(&data->locks->table_forks_lock);
}

void	release_right_fork(t_data *data)
{
	int		id;
	int		num_philosophers;
	t_locks	*locks;

	id = data->id;
	num_philosophers = data->simulation->num_philosophers;
	locks = data->locks;
	philosopher_log("has released right fork\n", data,
		&(locks->print_lock));
	sem_post(&data->locks->table_forks_lock);
}

int	he_releases_forks(t_data *data)
{
	int		id;
	int		num_philosophers;
	t_locks	*locks;

	id = data->id;
	num_philosophers = data->simulation->num_philosophers;
	locks = data->locks;
	if (data->simulation->philosopher_died_flag)
		return (1);
	release_left_fork(data);
	release_right_fork(data);
	return (0);
}
