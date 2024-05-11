#include "philo_bonus.h"

int	every_philosopher_is_full(t_simulation *simulation,
		t_data *data)
{
	unsigned long	i;

	i = 0;
	while (i < simulation->num_philosophers)
	{
		if (data[i].total_meals == false)
			return (0);
		i++;
	}
	return (1);
}

int	a_philosopher_died(unsigned long id, t_simulation *simulation,
		t_data *data)
{
	unsigned long	last_mealtime;

	sem_wait(&data->locks->mealtime_lock[id]);
	last_mealtime = get_timestamp() - data->last_mealtime;
	sem_post(&data->locks->mealtime_lock[id]);
	if (last_mealtime > simulation->time_to_die)
	{
		data->simulation->philosopher_died_flag = 1;
		sem_wait(&data->locks->print_lock);
		printf("%ld%s philosopher %ld ", get_timestamp()
			- simulation->starttime, "ms", data->id + 1);
		printf("%s", "died\n");
		sem_post(&data->locks->print_lock);
		return (1);
	}
	return (0);
}

int	a_philosopher_is_full(unsigned long id, t_simulation *simulation,
		t_data *data)
{
	unsigned long	meal_count;

	sem_wait(&data->locks->mealtime_lock[id]);
	meal_count = data->meal_count;
	sem_post(&data->locks->mealtime_lock[id]);
	if (meal_count >= simulation->num_must_eat)
		return (1);
	return (0);
}

void	observe_table(t_data *everyones_data, t_simulation *simulation)
{
	unsigned long	id;
	t_data 			*data;

	id = 0;
	while (1)
	{
		data = &everyones_data[id];
		if (a_philosopher_died(id, simulation, data))
			break ;
		if (a_philosopher_is_full(id, simulation, data))
			data->total_meals = true;
		if (simulation->num_must_eat && every_philosopher_is_full(simulation,
				data))
			break ;
		id = (id + 1) % simulation->num_philosophers;
	}
}