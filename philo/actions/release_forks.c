#include "../philo.h"

void	release_left_fork(t_thread_data *thread_data)
{
	int				thread_id;
	int				num_philosophers;
	t_locks			*locks;

	thread_id = thread_data->thread_id;
	num_philosophers = thread_data->input_data->num_philosophers;
	locks = thread_data->locks;
	pthread_mutex_unlock(&(locks->thread_mutexes[thread_id]));
}

void	release_right_fork(t_thread_data *thread_data)
{
	int				thread_id;
	int				num_philosophers;
	t_locks			*locks;

	thread_id = thread_data->thread_id;
	num_philosophers = thread_data->input_data->num_philosophers;
	locks = thread_data->locks;
	pthread_mutex_unlock(&(locks->thread_mutexes[(thread_id + 1)
			% (num_philosophers)]));
}

int	he_releases_forks(t_thread_data *thread_data)
{
	int				thread_id;
	int				num_philosophers;
	t_locks			*locks;

	thread_id = thread_data->thread_id;
	num_philosophers = thread_data->input_data->num_philosophers;
	locks = thread_data->locks;
	if (locks->philosopher_died_flag)
		return (1);
	release_left_fork(thread_data);
	philosopher_log("has released left fork\n", thread_data, &(locks->print_lock));
	release_right_fork(thread_data);
	philosopher_log("has released right fork\n", thread_data, &(locks->print_lock));
	return (0);
}