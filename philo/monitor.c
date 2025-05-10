#include "philo.h"

int	verify_meal_completion(t_philo *philos)
{
	int	i;
	int	min;

	i = 1;
	pthread_mutex_lock(&philos[0].eat_times_mutex);
	min = philos[0].eat_times;
	pthread_mutex_unlock(&philos[0].eat_times_mutex);
	while (i < philos->shared_data->nb_philos)
	{
		pthread_mutex_lock(&philos[i].eat_times_mutex);
		if (philos[i].eat_times < min)
			min = philos[i].eat_times;
		pthread_mutex_unlock(&philos[i].eat_times_mutex);
		i++;
	}
	if (min >= philos->shared_data->max_eats)
	{
		pthread_mutex_lock(&philos->shared_data->die);
		philos->shared_data->stop = 1;
		pthread_mutex_unlock(&philos->shared_data->die);
		return (1);
	}
	return (0);
}

int	detect_death(t_philo *philos, int i)
{
	long	current_time;

	pthread_mutex_lock(&philos[i].last_meal_time_mutex);
	current_time = get_current_time();
	if (current_time
		- philos[i].last_meal_time > philos->shared_data->time_to_die)
	{
		pthread_mutex_unlock(&philos[i].last_meal_time_mutex);
		pthread_mutex_lock(&philos->shared_data->die);
		philos->shared_data->stop = 1;
		pthread_mutex_unlock(&philos->shared_data->die);
		philos->shared_data->dead_philo = i + 1;
		return (1);
	}
	pthread_mutex_unlock(&philos[i].last_meal_time_mutex);
	return (0);
}

void	*monitor(void *arg)
{
	t_philo	*philos;
	int		i;

	philos = (t_philo *)arg;
	while (1)
	{
		i = 0;
		while (i < philos->shared_data->nb_philos)
		{
			if (detect_death(philos, i) == 1)
				return (NULL);
			if (philos->shared_data->max_eats != 0
				&& verify_meal_completion(philos) == 1)
				return (NULL);
			i++;
		}
		// ft_usleep(1000);
	}
}
