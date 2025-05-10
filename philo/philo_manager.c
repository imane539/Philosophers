#include "philo.h"

void	sleep_and_think(t_philo *philo)
{
	mutex_print(philo->shared_data, "is sleeping", philo->id, 'p');
	ft_usleep(philo->shared_data->time_to_sleep * 1000);
	mutex_print(philo->shared_data, "is thinking", philo->id, 'p');
	ft_usleep(philo->max_think_time * 1000);
}

void	eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->shared_data->mutex_forks[philo->first_fork]);
	mutex_print(philo->shared_data, "has taken a fork", philo->id, 'p');
	if (philo->shared_data->nb_philos == 1)
	{
		ft_usleep(philo->shared_data->time_to_die * 1000);
		pthread_mutex_unlock(&philo->shared_data->mutex_forks
		[philo->first_fork]);
		return ;
	}
	pthread_mutex_lock(&philo->shared_data->mutex_forks[philo->second_fork]);
	mutex_print(philo->shared_data, "has taken a fork", philo->id, 'p');
	pthread_mutex_lock(&philo->eat_times_mutex);
	philo->eat_times++;
	pthread_mutex_unlock(&philo->eat_times_mutex);
	mutex_print(philo->shared_data, "is eating", philo->id, 'p');
	pthread_mutex_lock(&philo->last_meal_time_mutex);
	philo->last_meal_time = get_current_time();
	pthread_mutex_unlock(&philo->last_meal_time_mutex);
	ft_usleep(philo->shared_data->time_to_eat * 1000);
	pthread_mutex_unlock(&philo->shared_data->mutex_forks[philo->second_fork]);
	pthread_mutex_unlock(&philo->shared_data->mutex_forks[philo->first_fork]);
	sleep_and_think(philo);
}

void	*philosopher(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	if (philo->id % 2 == 0)
		ft_usleep(50 * 1000);
	init_forks_order(philo);
	while (1)
	{
		pthread_mutex_lock(&philo->shared_data->die);
		if (philo->shared_data->stop != 0)
		{
			pthread_mutex_unlock(&philo->shared_data->die);
			return (NULL);
		}
		pthread_mutex_unlock(&philo->shared_data->die);
		philo->max_think_time = philo->shared_data->time_to_die
			- (philo->shared_data->time_to_eat
				+ philo->shared_data->time_to_sleep) - 10;
		if (philo->max_think_time < 0)
			philo->max_think_time = 0;
		eat(philo);
	}
	return (NULL);
}

t_philo	*create_philos(t_philo *philos, t_shared_data *shared_data)
{
	int	i;

	i = 0;
	philos = malloc(sizeof(t_philo) * shared_data->nb_philos);
	while (i < shared_data->nb_philos)
	{
		philos[i].id = i;
		philos[i].shared_data = shared_data;
		philos[i].last_meal_time = shared_data->current_time;
		philos[i].eat_times = 0;
		pthread_mutex_init(&philos[i].eat_times_mutex, NULL);
		pthread_mutex_init(&philos[i].last_meal_time_mutex, NULL);
		pthread_create(&philos[i].thread, NULL, philosopher, &philos[i]);
		i++;
	}
	return (philos);
}

void	finalize_simulation(t_philo *philos, t_shared_data *shared_data,
		pthread_t monitor_thread)
{
	void	*res;
	int		i;

	i = 0;
	pthread_join(monitor_thread, &res);
	if (res == NULL && shared_data->dead_philo != 0)
		mutex_print(shared_data, "died", shared_data->dead_philo, 'm');
	while (i < shared_data->nb_philos)
	{
		pthread_join(philos[i].thread, NULL);
		i++;
	}
	i = 0;
	while (i < shared_data->nb_philos)
	{
		pthread_mutex_destroy(&shared_data->mutex_forks[i]);
		i++;
	}
}
