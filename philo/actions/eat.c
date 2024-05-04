#include "../philo.h"

void	he_eats(t_thread_data *thread_data)
{
	int				thread_id;
	t_locks			*locks;

	thread_id = thread_data->thread_id;
	locks = thread_data->locks;
	philosopher_log("is eating\n", thread_id, &(locks->print_lock));
	usleep(thread_data->input_data->time_to_eat * 1000);
	set_last_mealtime(thread_data, &locks->mealtime_lock);
}
