#include "philo.h"

void	set_last_mealtime(t_thread_data *thread_data, pthread_mutex_t *mealtime_lock)
{
	pthread_mutex_lock(mealtime_lock);
	thread_data->starttime = get_timestamp();
	pthread_mutex_unlock(mealtime_lock);
}