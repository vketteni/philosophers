/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   think.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vketteni <vketteni@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 19:33:05 by vketteni          #+#    #+#             */
/*   Updated: 2024/05/07 19:33:07 by vketteni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo_bonus.h"

int	he_thinks(t_data *data)
{
	int		id;
	t_locks	*locks;

	id = data->id;
	locks = data->locks;
	if (data->simulation->philosopher_died_flag)
		return (1);
	philosopher_log("is thinking\n", data, &(locks->print_lock));
	return (0);
}
