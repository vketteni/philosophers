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

int	just_a_single_philosopher(t_data *data)
{
	while (data->simulation->num_philosophers == 1)
	{
		if (data->simulation->philosopher_died_flag)
			return (1);
		usleep(10000);
	}
	return (0);
}

void	pick_left_fork(t_data *data)
{
	int		id;

	id = data->id;
	sem_wait(&data->locks->table_forks_lock);
}

void	pick_right_fork(t_data *data)
{
	int		id;
	int		num_philosophers;

	id = data->id;
	num_philosophers = data->simulation->num_philosophers;
	sem_wait(&data->locks->table_forks_lock);
	philosopher_log("has taken the right fork\n", data,
		&(data->locks->print_lock));
}

int	he_picks_up_forks(t_data *data)
{
	int		id;

	id = data->id;
	if (data->simulation->philosopher_died_flag)
		return (1);
	pick_left_fork(data);
	if (just_a_single_philosopher(data))
		return (1);
	pick_right_fork(data);
	return (0);
}
