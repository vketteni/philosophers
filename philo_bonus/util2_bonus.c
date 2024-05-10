/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vketteni <vketteni@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 19:37:26 by vketteni          #+#    #+#             */
/*   Updated: 2024/05/07 19:37:29 by vketteni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

size_t	get_timestamp(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000 + tv.tv_usec / 1000));
}

void	philosopher_log(char *log_message, t_thread_data *thread_data)
{
	unsigned long	starttime;
	long			thread_id;

	thread_id = thread_data->thread_id;
	starttime = thread_data->simulation->starttime;

	if (!thread_data->simulation->philosopher_died_flag)
	{
		printf("%ldms philosopher %ld ", get_timestamp() - starttime, thread_id
			+ 1);
		printf("%s", log_message);
	}
}
