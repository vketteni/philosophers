#include "philo.h"

size_t	get_timestamp(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000 + tv.tv_usec / 1000));
}

void	philosopher_log(char *log_message, t_thread_data *thread_data, pthread_mutex_t *print_lock)
{
	unsigned long	starttime;
	long			thread_id;

	if (thread_data->locks->philosopher_died_flag)
		return ;
	thread_id = thread_data->thread_id;
	starttime = thread_data->starttime;
	pthread_mutex_lock(print_lock);
	printf("%ld %ld ", get_timestamp() - starttime, thread_id + 1);
	printf("%s", log_message);
	pthread_mutex_unlock(print_lock);
}