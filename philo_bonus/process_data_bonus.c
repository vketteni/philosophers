/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initializers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vketteni <vketteni@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 13:57:33 by vketteni          #+#    #+#             */
/*   Updated: 2024/05/01 13:57:35 by vketteni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

t_simulation	*initialize_simulation(int argc, const char **argv)
{
	t_simulation	*simulation;

	simulation = (t_simulation *)malloc(sizeof(t_simulation));
	if (!simulation)
		return (NULL);
	simulation->num_philosophers = ft_atoi(argv[1]);
	simulation->time_to_die = ft_atoi(argv[2]);
	simulation->time_to_eat = ft_atoi(argv[3]);
	simulation->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		simulation->num_must_eat = ft_atoi(argv[5]);
	simulation->philosopher_died_flag = 0;
	simulation->starttime = 0;
	return (simulation);
}

t_data	*initialize_process_data(t_locks *locks,
		t_simulation *simulation)
{
	t_data	*data;
	unsigned long	i;

	if (!simulation)
		return (NULL);
	data = (t_data *)malloc(sizeof(t_data)
			* simulation->num_philosophers);
	if (!data)
		return (NULL);
	i = 0;
	while (i < simulation->num_philosophers)
	{
		data[i].last_mealtime = 0;
		data[i].meal_count = 0;
		data[i].total_meals = false;
		data[i].simulation = simulation;
		data[i].locks = locks;
		data[i].id = i;
		i++;
	}
	return (data);
}
