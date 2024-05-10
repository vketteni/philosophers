#include "philo_bonus.h"

int	main(int argc, char **argv)
{
	unsigned long i;
	pid_t pid;
	t_thread_data *threads_data;
	pthread_t *threads;
	t_simulation_data *simulation;
	t_locks *locks;

	if (check_arguments(argc, argv))
		return (EXIT_FAILURE);
	simulation = initialize_simulation(argc, argv);
	if (simulation->num_philosophers == 0)
		return (EXIT_SUCCESS);
	locks = create_locks(simulation->num_philosophers);
	process_data = initialize_process_data(forks, simulation);
	if (!process_data)
		return (free_memory(forks, simulation));

	simulation->starttime = get_timestamp();
	i = 0;
	while (i < simulation->num_philosophers)
	{
		pid = fork();
		if (pid == 0)
			philosopher_process((void *)&threads_data[i]);
		else
			(0);
		i++;
	}
	usleep(100 * simulation->num_philosophers);
	return (EXIT_SUCCESS);
}