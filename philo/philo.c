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

pthread_mutex_t lock;

void* printTimestamp(void *arg) {
    // Get the current time
    time_t rawtime;
    time(&rawtime);
    struct tm *timeinfo = localtime(&rawtime);

    // Convert time to string
    char buffer[80];
    strftime(buffer, 80, "%Y-%m-%d %H:%M:%S", timeinfo);

    // Print the timestamp
    printf("Thread %ld: %s\n", (long)arg, buffer);

    // Sleep for a random time between 1 to 4 seconds
    usleep((rand() % 4 + 1) * 1000000);  // 1 second = 1,000,000 microseconds

    return NULL;
}

void	*thread_routine(void *arg)
{
	long	thread_id;
	struct	timeval tv;

	thread_id = (long)arg;
	gettimeofday(&tv, NULL);
	
	pthread_mutex_lock(&lock);
	ft_putstr_fd("Hi philosopher ", STDERR_FILENO);
	ft_putnbr_fd((int)thread_id, STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
	ft_putstr_fd("Timestamp ", STDERR_FILENO);
	ft_putnbr_fd((int)(tv.tv_usec / 1000), STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
	pthread_mutex_unlock(&lock);
	return (NULL);
}

int	main(int argc, char **argv)
{
	pthread_t	threads[ft_atoi(argv[1])];
	long		i;

	if (argc < 4 || argc > 5)
	{
		ft_putendl_fd("Correct use: philo number_of_philosophers "
						"time_to_die time_to_eat time_to_sleep "
						"[number_of_times_each_philosopher_must_eat]",
						STDERR_FILENO);
		return (1);
	}
	if (pthread_mutex_init(&lock, NULL) != 0)
	{
		ft_putendl_fd("Failed to initialize mutext.", STDERR_FILENO);
		return (1);
	}
	i = 0;
	ft_putstr_fd("Number of philosophers: ", STDERR_FILENO);
	ft_putendl_fd(argv[1], STDERR_FILENO);
	while (i < ft_atoi(argv[1]))
	{
		ft_putstr_fd("Create thread ", STDERR_FILENO);
		ft_putnbr_fd(i, STDERR_FILENO);
		ft_putendl_fd("", STDERR_FILENO);
		pthread_create(&threads[i], NULL, printTimestamp,
			(void *)i);
		i++;
	}

	i = 0;
	while (i < ft_atoi(argv[1]))
	{
		pthread_join(threads[i], NULL);
		ft_putstr_fd("Thread ", STDERR_FILENO);
		ft_putnbr_fd(i, STDERR_FILENO);
		ft_putendl_fd(" ended", STDERR_FILENO);
		i++;
	}
	ft_putendl_fd("All threads completed.", STDERR_FILENO);
	return (0);
}
