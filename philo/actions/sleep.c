#include "../philo.h"

void	he_sleeps(t_thread_data *thread_data)
{
	int		thread_id;
	t_locks	*locks;

	thread_id = thread_data->thread_id;
	locks = thread_data->locks;
	philosopher_log("is sleeping\n", thread_id, &(locks->print_lock));
	usleep(thread_data->input_data->time_to_sleep * 1000);
}

