/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   observe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vketteni <vketteni@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 19:34:02 by vketteni          #+#    #+#             */
/*   Updated: 2024/05/07 19:34:04 by vketteni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	every_philosopher_is_full(t_simulation_data *simulation,
		t_thread_data *thread_data)
{
	unsigned long	i;

	i = 0;
	while (i < simulation->num_philosophers)
	{
		if (thread_data[i].total_meals == false)
			return (0);
		i++;
	}
	return (1);
}

int	a_philosopher_died(unsigned long thread_id, t_simulation_data *simulation,
		t_thread_data *thread_data)
{
	unsigned long	last_mealtime;

	pthread_mutex_lock(&thread_data->locks->mealtime_mutexes[thread_id]);
	last_mealtime = get_timestamp() - thread_data->last_mealtime;
	pthread_mutex_unlock(&thread_data->locks->mealtime_mutexes[thread_id]);
	if (last_mealtime > simulation->time_to_die)
	{
		thread_data->simulation->philosopher_died_flag = 1;
		pthread_mutex_lock(&thread_data->locks->print_lock);
		printf("%ld%s philosopher %ld ", get_timestamp()
			- simulation->starttime, "ms", thread_data->thread_id + 1);
		printf("%s", "died\n");
		pthread_mutex_unlock(&thread_data->locks->print_lock);
		return (1);
	}
	return (0);
}

int	a_philosopher_is_full(unsigned long thread_id, t_simulation_data *simulation,
		t_thread_data *thread_data)
{
	unsigned long	meal_count;

	pthread_mutex_lock(&thread_data->locks->mealtime_mutexes[thread_id]);
	meal_count = thread_data->meal_count;
	pthread_mutex_unlock(&thread_data->locks->mealtime_mutexes[thread_id]);
	if (meal_count >= simulation->num_must_eat)
		return (1);
	return (0);
}

void	observe_the_round_table(t_thread_data *threads_data,
		t_simulation_data *simulation)
{
	int				thread_id;
	t_thread_data	*thread_data;

	thread_id = 0;
	while (1)
	{
		thread_data = &threads_data[thread_id];
		if (a_philosopher_died(thread_id, simulation, thread_data))
			break ;
		if (a_philosopher_is_full(thread_id, simulation, thread_data))
			thread_data->total_meals = true;
		if (simulation->num_must_eat && every_philosopher_is_full(simulation,
				thread_data))
			break ;
		thread_id = (thread_id + 1) % simulation->num_philosophers;
	}
}
