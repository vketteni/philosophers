#include "../philo.h"

void	pick_left_fork(t_thread_data *thread_data)
{
	int		thread_id;
	t_locks	*locks;

	thread_id = thread_data->thread_id;
	locks = thread_data->locks;
	pthread_mutex_lock(&(locks->thread_mutexes[thread_id]));
}

void	pick_right_fork(t_thread_data *thread_data)
{
	int		thread_id;
	t_locks	*locks;
	int		num_philosophers;

	thread_id = thread_data->thread_id;
	num_philosophers = thread_data->input_data->num_philosophers;
	locks = thread_data->locks;
	pthread_mutex_lock(&(locks->thread_mutexes[(thread_id + 1)
			% (num_philosophers)]));
}

void	he_picks_up_forks(t_thread_data *thread_data)
{
	int		thread_id;
	t_locks	*locks;

	thread_id = thread_data->thread_id;
	locks = thread_data->locks;
	pick_left_fork(thread_data);
	philosopher_log("has taken a fork\n", thread_id, &(locks->print_lock));
	pick_right_fork(thread_data);
	philosopher_log("has taken a fork\n", thread_id, &(locks->print_lock));
}