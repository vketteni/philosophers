#include "philo.h"

void	*thread_routine(void *arg)
{
	t_thread_data	*thread_data;


	thread_data = (t_thread_data *)arg;
	set_last_mealtime(thread_data, &thread_data->locks->mealtime_lock);
	if (thread_data->thread_id % 2 == 0)
		usleep(thread_data->input_data->time_to_eat * 1000);
	while (1)
	{
		he_picks_up_forks(thread_data);
		he_eats(thread_data);
		he_releases_forks(thread_data);
		he_sleeps(thread_data);
		he_thinks(thread_data);
	}
	return (NULL);
}
