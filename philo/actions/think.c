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

#include "../philo.h"

int	he_thinks(t_thread_data *thread_data)
{
	int		thread_id;
	t_locks	*locks;

	thread_id = thread_data->thread_id;
	locks = thread_data->locks;
	philosopher_log("is thinking\n", thread_data, &(locks->print_lock));
	return (0);
}
