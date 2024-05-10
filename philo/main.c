/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vketteni <vketteni@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 11:11:44 by vketteni          #+#    #+#             */
/*   Updated: 2024/04/29 11:11:46 by vketteni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	start_philosopher_meeting(t_thread_data *threads_data,
		t_simulation_data *simulation)
{
	unsigned long	i;

	simulation->starttime = get_timestamp();
	i = 0;
	while (i < simulation->num_philosophers)
	{
		pthread_create(&(threads_data[i].thread), NULL, thread_routine,
			(void *)&(threads_data[i]));
		i++;
	}
	usleep(100 * simulation->num_philosophers);
}

void	close_the_meeting(t_thread_data *threads_data, t_simulation_data *simulation)
{
	unsigned long	i;

	i = 0;
	while (i < simulation->num_philosophers)
	{
		pthread_join(threads_data[i].thread, NULL);
		i++;
	}
	i = 0;
	while (i < simulation->num_philosophers)
	{
		pthread_mutex_destroy(&threads_data[i].locks->mealtime_mutexes[i]);
		pthread_mutex_destroy(&threads_data[i].locks->thread_mutexes[i]);
		i++;
	}
	i = 0;
	pthread_mutex_destroy(&threads_data[i].locks->print_lock);
	pthread_mutex_destroy(&threads_data[i].locks->total_meals_lock);
	pthread_mutex_destroy(&threads_data[i].locks->starttime_lock);
}

int	philosophers(t_locks *locks, t_simulation_data *simulation)
{
	t_thread_data	*threads_data;
	pthread_t		*threads;

	if (!locks || !simulation)
		return (EXIT_FAILURE);
	if (simulation->num_philosophers == 0)
		return (EXIT_SUCCESS);
	threads = initialize_threads(simulation->num_philosophers);
	if (!threads)
		return (free_memory(locks, NULL, simulation));
	threads_data = initialize_threads_data(threads, locks, simulation);
	if (!threads_data)
		return (free_memory(locks, threads, simulation));
	start_philosopher_meeting(threads_data, simulation);
	observe_the_round_table(threads_data, simulation);
	close_the_meeting(threads_data, simulation);
	free(threads);
	free(threads_data);
	return (EXIT_SUCCESS);
}

int	main(int argc, const char **argv)
{
	t_locks			*locks;
	t_simulation_data	*simulation;

	if (check_arguments(argc, argv))
		return (EXIT_FAILURE);
	simulation = initialize_simulation(argc, argv);
	if (!simulation)
		return (free_memory(NULL, NULL, NULL));
	locks = create_locks(simulation);
	if (!locks)
		return (EXIT_FAILURE);
	if (philosophers(locks, simulation))
		return (free_memory(locks, NULL, simulation));
	free_memory(locks, NULL, simulation);
	return (EXIT_SUCCESS);
}
