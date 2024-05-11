#include "philo_bonus.h"

int	main(int argc, char **argv)
{
	unsigned long i;
	t_data *data;
	t_simulation *simulation;
	t_locks *locks;

	if (check_arguments(argc, argv))
		return (EXIT_FAILURE);
	simulation = initialize_simulation(argc, argv);
	if (simulation->num_philosophers == 0)
		return (EXIT_SUCCESS);
	locks = create_locks(simulation->num_philosophers);
	data = initialize_process_data(locks, simulation);
	if (!data)
		return (free_memory(locks, simulation));
	simulation->starttime = get_timestamp();
	i = 0;
	while (i < simulation->num_philosophers)
	{
		if (fork() == 0)
			return (philosopher_process((void *)&data[i]));
		i++;
	}
	usleep(100 * simulation->num_philosophers);
	return (EXIT_SUCCESS);
}