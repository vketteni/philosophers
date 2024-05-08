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
	pthread_mutex_t	*mealtime_mutexes;
	pthread_mutex_t	print_lock;
	pthread_mutex_t	starttime_lock;
	pthread_mutex_t	total_meals_lock;
}					t_locks;

typedef struct s_simulation_data
{
	unsigned long	num_philosophers;
	unsigned long	time_to_die;
	unsigned long	time_to_eat;
	unsigned long	time_to_sleep;
	unsigned long	num_must_eat;
	unsigned long	starttime;
	unsigned long	philosopher_died_flag;
}					t_simulation;

typedef struct s_thread_data
{
	pthread_t		thread;
	long			meal_count;
	long			thread_id;
	t_simulation	*simulation;
	size_t			last_mealtime;
	bool			total_meals;
	t_locks			*locks;

}					t_thread_data;

void				*thread_routine(void *arg);
size_t				get_timestamp(void);
void				philosopher_log(char *format_string,
						t_thread_data *thread_data,
						pthread_mutex_t *print_lock);
int					he_picks_up_forks(t_thread_data *thread_data);
int					he_sleeps(t_thread_data *thread_data);
int					he_eats(t_thread_data *thread_data);
int					he_releases_forks(t_thread_data *thread_data);
int					he_thinks(t_thread_data *thread_data);
int					ft_isdigit(unsigned int c);
int					ft_strncmp(char *s1, char *s2, size_t n);
int					ft_atoi(const char *nptr);
int					check_arguments(int argc, const char **argv);
int					free_memory(t_locks *mutexes, pthread_t *threads,
						t_simulation *data);
t_thread_data		*initialize_thread_data(pthread_t *threads, t_locks *locks,
						t_simulation *data);
pthread_t			*initialize_threads(size_t num_threads);
t_simulation		*initialize_simulation(int argc, const char **argv);
t_locks				*initialize_locks(t_locks *locks, t_simulation *data);
t_locks				*create_locks(t_simulation *data);
void				observe_the_round_table(t_thread_data *threads_data,
						t_simulation *simulation);
#endif