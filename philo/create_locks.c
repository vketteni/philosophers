#include "philo.h"

t_locks	*initialize_locks(t_locks *locks, t_data *data)
{
	int			i;

	if (!data)
		return (NULL);
	i = 0;
	while (i < data->num_philosophers)
	{
		if (pthread_mutex_init(&(locks->thread_mutexes[i]), NULL)
			|| pthread_mutex_init(&(locks->mealtime_mutexes[i]), NULL))
			return (NULL);
		i++;
	}
	if (pthread_mutex_init(&(locks->print_lock), NULL)
		|| pthread_mutex_init(&(locks->total_meals_lock), NULL))
		return (NULL);
	locks->starttime_flag = 0;
	locks->philosopher_died_flag = 0;
	return (locks);
}

t_locks	*create_locks(t_data *data)
{
	t_locks 		*mutexes;

	if (!data)
		return (NULL);
	mutexes = (t_locks *)malloc(sizeof(t_locks));
	if (!mutexes)
		return (NULL);
	mutexes->thread_mutexes = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * data->num_philosophers);
	if (!mutexes->thread_mutexes)
		return (NULL);
	mutexes->mealtime_mutexes = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * data->num_philosophers);
	if (!mutexes->mealtime_mutexes)
	{
		free_memory(mutexes, NULL, NULL);
		return (NULL);
	}
	if (!initialize_locks(mutexes, data))
	{
		free_memory(mutexes, NULL, NULL);
		return (NULL);
	}
	return (mutexes);
}