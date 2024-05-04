#include "../philo.h"

void	he_thinks(t_thread_data *thread_data)
{
	int		thread_id;
	t_locks	*locks;

	thread_id = thread_data->thread_id;
	locks = thread_data->locks;
	philosopher_log("is thinking\n", thread_id, &(locks->print_lock));
}
