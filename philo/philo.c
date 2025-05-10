#include "philo.h"
void ft_usleep(unsigned int usec)
{
    long start_time;
    long ms;

    start_time = get_current_time();
    usleep(usec * 0.7);
    ms = usec/1000;
    while (get_current_time() - start_time < ms)
        usleep(100);
}

void	mutex_print(t_shared_data *shared_data, char *msg, int id, char check)
{
	if (check == 'm')
	{
		pthread_mutex_lock(&shared_data->mtx_print);
		printf("%ld %d %s\n", get_current_time(), shared_data->dead_philo, msg);
		pthread_mutex_unlock(&shared_data->mtx_print);
		return ;
	}
	pthread_mutex_lock(&shared_data->die);
	if (shared_data->stop != 0)
	{
		pthread_mutex_unlock(&shared_data->die);
		return ;
	}
	pthread_mutex_unlock(&shared_data->die);
	pthread_mutex_lock(&shared_data->mtx_print);
	printf("%ld %d %s\n", get_current_time(), id + 1, msg);
	pthread_mutex_unlock(&shared_data->mtx_print);
}

void	fill_shared_data(t_shared_data *shared_data, int *num)
{
	int	i;

	i = 0;
	shared_data->stop = 0;
	shared_data->nb_philos = num[0];
	shared_data->time_to_die = num[1];
	shared_data->time_to_eat = num[2];
	shared_data->time_to_sleep = num[3];
	shared_data->dead_philo = 0;
	shared_data->mutex_forks = malloc(sizeof(pthread_mutex_t)
			* shared_data->nb_philos);
	shared_data->current_time = get_current_time();
	while (i < shared_data->nb_philos)
		pthread_mutex_init(&shared_data->mutex_forks[i++], NULL);
	pthread_mutex_init(&shared_data->mtx_print, NULL);
	pthread_mutex_init(&shared_data->die, NULL);
}

int	main(int ac, char **av)
{
	int				*num;
	t_shared_data	shared_data;
	t_philo			*philos;
	pthread_t		monitor_thread;

	philos = NULL;
	if (ac < 5 || ac > 6)
	{
		printf("number of arg invalid");
		return (1);
	}
	num = check_argument(ac, av);
	if (num == NULL)
		return (1);
	if(ac == 5)
		shared_data.max_eats = 0;
	else
		shared_data.max_eats = num[4];
	fill_shared_data(&shared_data, num);
	free(num);
	philos = create_philos(philos, &shared_data);
	pthread_create(&monitor_thread, NULL, monitor, philos);
	finalize_simulation(philos, &shared_data, monitor_thread);
	free(shared_data.mutex_forks);
	free(philos);
}
