#include "philo_bonus.h"

t_locks *create_locks(t_simulation_data *simulation)
{
	t_locks	*locks;

	locks = (t_locks *)malloc(sizeof(t_locks));
	if (!locks)
		return (NULL);
	sem_init(&locks->table_forks, 0, simulation->num_philosophers);
	return (locks);
}