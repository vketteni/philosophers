#include "../philo.h"

int	he_thinks(t_thread_data *thread_data)
{
	int		thread_id;
	t_locks	*locks;

	thread_id = thread_data->thread_id;
	locks = thread_data->locks;
	if (locks->philosopher_died_flag)
		return (1);
	philosopher_log("is thinking\n", thread_data, &(locks->print_lock));
	return (0);
}
