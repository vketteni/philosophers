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

void	philosopher_log(char *log_message, t_data *data, sem_t *print_lock)
{
	unsigned long	starttime;
	long			id;

	id = data->id;
	starttime = data->simulation->starttime;

	sem_wait(print_lock);
	if (!data->simulation->philosopher_died_flag)
	{
		printf("%ldms philosopher %ld ", get_timestamp() - starttime, id
			+ 1);
		printf("%s", log_message);
	}
	sem_post(print_lock);
}
