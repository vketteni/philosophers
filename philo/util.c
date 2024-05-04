#include "philo.h"

size_t	get_timestamp(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000 + tv.tv_usec / 1000));
}

void	philosopher_log(char *log_message, long thread_id, pthread_mutex_t *print_lock)
{
	pthread_mutex_lock(print_lock);
	printf("%ld %ld ", get_timestamp(), thread_id);
	printf("%s", log_message);
	pthread_mutex_unlock(print_lock);
}