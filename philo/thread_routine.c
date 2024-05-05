#include "philo.h"

void	set_starttime(t_thread_data *thread_data)
{
	while (thread_data->locks->starttime_flag == 0)
		usleep(200);
	set_last_mealtime(thread_data,
		&thread_data->locks->mealtime_mutexes[thread_data->thread_id]);
	thread_data->starttime = thread_data->mealtime;
}

void	*thread_routine(void *arg)
{
	t_thread_data	*thread_data;

	thread_data = (t_thread_data *)arg;
	set_starttime(thread_data);
	if (thread_data->thread_id % 2 == 0)
		usleep(thread_data->input_data->time_to_eat * 1000);
	while (1)
	{
		if (he_picks_up_forks(thread_data) || he_eats(thread_data)
			|| he_releases_forks(thread_data) || he_sleeps(thread_data)
			|| he_thinks(thread_data))
			break ;
	}
	return (NULL);
}
