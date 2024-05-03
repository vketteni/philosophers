/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vketteni <vketteni@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 11:11:34 by vketteni          #+#    #+#             */
/*   Updated: 2024/04/29 11:11:37 by vketteni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <limits.h>
# include <pthread.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_locks
{
	pthread_mutex_t	*thread_mutexes;
	pthread_mutex_t	print_lock;
	pthread_mutex_t	last_meal_lock;
	pthread_mutex_t	total_meals_lock;
}					t_locks;

typedef struct s_data
{
	int				num_philosophers;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				num_must_eat;
}					t_data;

typedef struct s_thread_data
{
	pthread_t		thread;
	long			thread_id;
	t_data			data;
	long			starttime;
	pthread_mutex_t	*thread_lock;
	pthread_mutex_t	*print_lock;
	pthread_mutex_t	*last_meal_lock;
	pthread_mutex_t	*total_meals_lock;
	
}					t_thread_data;

int					ft_isdigit(unsigned int c);
int					ft_strncmp(char *s1, char *s2, size_t n);
int					ft_atoi(const char *nptr);
int					check_arguments(int argc, const char **argv);
int					free_memory(t_locks *mutexes, pthread_t *threads,
						t_data *data);
t_thread_data		*initialize_thread_data(t_locks *locks, t_data *data);
pthread_t			*initialize_threads(size_t num_threads);
t_data				*initialize_data(int argc, const char **argv);
pthread_mutex_t		*initialize_forks(t_data *data);
t_locks				*initialize_mutexes(t_data *data);

/*
	Allowed functions:
		memset, printf, malloc, free, write,
		usleep, gettimeofday, pthread_create,
		pthread_detach, pthread_join, pthread_mutex_init,
		pthread_mutex_destroy, pthread_mutex_lock,
		pthread_mutex_unlock
 */

#endif