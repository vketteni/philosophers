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
			t_simulation *simulation)
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

void	close_the_meeting(t_thread_data *thread_data, t_simulation *simulation)
{
	unsigned long	i;

	i = 0;
	while (i < simulation->num_philosophers)
		pthread_join(thread_data[i++].thread, NULL);
}

int	philosophers(t_locks *locks, t_simulation *simulation)
{
	t_thread_data	*threads_data;
	pthread_t		*threads;

	if (!locks || !simulation)
		return (EXIT_FAILURE);
	threads = initialize_threads(simulation->num_philosophers);
	if (!threads)
		return (free_memory(locks, NULL, simulation));
	threads_data = initialize_thread_data(threads, locks, simulation);
	if (!threads_data)
		return (free_memory(locks, threads, simulation));
	start_philosopher_meeting(threads_data, simulation);
	observe_the_round_table(threads_data);
	close_the_meeting(threads_data, simulation);
	return (EXIT_SUCCESS);
}

int	main(int argc, const char **argv)
{
	t_locks			*locks;
	t_simulation	*data;

	if (check_arguments(argc, argv))
		return (EXIT_FAILURE);
	data = initialize_input(argc, argv);
	if (!data)
		return (free_memory(NULL, NULL, NULL));
	locks = create_locks(data);
	if (!locks)
		return (EXIT_FAILURE);
	if (philosophers(locks, data))
		return (free_memory(locks, NULL, data));
	free_memory(locks, NULL, NULL);
	return (EXIT_SUCCESS);
}
