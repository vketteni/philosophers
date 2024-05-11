#include "philo_bonus.h"

void	*terminate_locks(t_locks *locks, t_simulation *simulation)
{
	unsigned long	i;
	
	if (!locks)
		return (NULL);
	if (locks->mealtime_lock)
	{
		i = 0;
		while (i < simulation->num_philosophers)
			sem_destroy(&locks->mealtime_lock[i++]);
	}
	if (locks->mealtime_lock)
	{
		i = 0;
		while (i < simulation->num_philosophers)
			sem_destroy(&locks->total_meals_lock[i++]);
	}
	sem_destroy(&locks->table_forks_lock);
	sem_destroy(&locks->print_lock);
	return (NULL);
}

t_locks *create_locks(t_simulation *simulation)
{
	unsigned long	i;
	t_locks	*locks;

	locks = (t_locks *)malloc(sizeof(t_locks));
	if (!locks)
		return (NULL);
	memset(locks, 0, sizeof(t_locks));
	sem_init(&locks->table_forks_lock, 0, simulation->num_philosophers);
	sem_init(&locks->print_lock, 0, 1);
	locks->mealtime_lock = (sem_t *)malloc(sizeof(sem_t) * simulation->num_philosophers);
	if (!locks->mealtime_lock)
		return (terminate_locks(locks, simulation));
	i = 0;
	while (i < simulation->num_philosophers)
		sem_init(&locks->mealtime_lock[i++], 0, 1);
	locks->total_meals_lock = (sem_t *)malloc(sizeof(sem_t) * simulation->num_philosophers);
	if (!locks->total_meals_lock)
		return (terminate_locks(locks, simulation));
	i = 0;
	while (i < simulation->num_philosophers)
		sem_init(&locks->mealtime_lock[i++], 0, 1);
	return (locks);
}