#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <pthread.h>
# include <semaphore.h>
# include <stdbool.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_locks
{
	sem_t			table_forks;
}					t_locks;

typedef struct s_simulation
{
	unsigned long	num_philosophers;
	unsigned long	time_to_die;
	unsigned long	time_to_eat;
	unsigned long	time_to_sleep;
	unsigned long	num_must_eat;
	unsigned long	starttime;
	unsigned long	philosopher_died_flag;
}					t_simulation;

typedef struct s_data
{
	long			meal_count;
	t_simulation	*simulation;
	t_locks			*locks;
	size_t			last_mealtime;
	bool			total_meals;
}					t_data;

void				*philo_process(void *arg);
size_t				get_timestamp(void);
void				philosopher_log(char *format_string, t_data *thread_data);
int					he_picks_up_forks(t_data *thread_data);
int					he_sleeps(t_data *thread_data);
int					he_eats(t_data *thread_data);
int					he_releases_forks(t_data *thread_data);
int					he_thinks(t_data *thread_data);
int					ft_isdigit(unsigned int c);
int					ft_strncmp(char *s1, char *s2, size_t n);
int					ft_atoi(const char *nptr);
int					check_arguments(int argc, const char **argv);
t_locks				*create_locks(t_simulation *simulation);
int					free_memory(sem_t *semaphore, t_simulation *data);
t_data				*initialize_threads_data(pthread_t *threads,
						t_simulation *data);
pthread_t			*initialize_threads(size_t num_threads);
t_simulation		*initialize_simulation(int argc, const char **argv);
// void					observe_the_round_table(t_data *threads_data,
// 							t_simulation *simulation);

/*	Allowed function (BONUS)
	memset, printf, malloc, free, write, fork, kill,
	exit, pthread_create, pthread_detach, pthread_join,
	usleep, gettimeofday, waitpid, sem_open, sem_close,
	sem_post, sem_wait, sem_unlink
*/
#endif