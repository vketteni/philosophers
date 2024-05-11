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

#include "../philo_bonus.h"

int	he_sleeps(t_data *data)
{
	int		id;
	t_locks	*locks;

	id = data->id;
	locks = data->locks;
	if (data->simulation->philosopher_died_flag)
		return (1);
	philosopher_log("is sleeping\n", data, &(locks->print_lock));
	usleep(data->simulation->time_to_sleep * 1000);
	return (0);
}
