#include "philo_bonus.h"

int	sleep_and_think(t_philo *philo)
{
	if(sema_print(philo, "is sleeping", philo->id , 'p')== 1)
		return 1;
	ft_usleep(philo->shared_data->time_to_sleep * 1000);
	if(sema_print(philo, "is thinking", philo->id , 'p')== 1)
		return 1;
	ft_usleep(philo->max_think_time * 1000);
	return 0;
}

int	eat(t_philo *philo)
{
	sem_wait(philo->shared_data->sem);
	if(sema_print(philo, "has taken a fork", philo->id , 'p') == 1)
		return 1;
	if (philo->shared_data->nb_philos == 1)
	{
		ft_usleep(philo->shared_data->time_to_die * 1000);	
		return 0;
	}
	sem_wait(philo->shared_data->sem);
	if(sema_print(philo, "has taken a fork", philo->id , 'p') == 1)
		return 1;
	philo->eat_times++;
	if(sema_print(philo, "is eating", philo->id , 'p') == 1)
		return 1;
	sem_wait(philo->sem_last_meal_time);
	philo->last_meal_time = get_current_time();
	sem_post(philo->sem_last_meal_time);
	ft_usleep(philo->shared_data->time_to_eat * 1000);
	sem_post(philo->shared_data->sem);
	sem_post(philo->shared_data->sem);
	if(sleep_and_think(philo) == 1)
		return 1;
	return 0;
}
void	philosopher(t_philo	*philo)
{
	pthread_create(&philo->monitor,NULL,detect_death,philo);
	pthread_create(&philo->death_blocker,NULL,death_blocker,philo);
	if (philo->id % 2 == 0)
		ft_usleep(50 * 1000);
	while (1)
	{
		sem_wait(philo->sem_stop);
		if (philo->stop_sim != 0)
		{
			sem_post(philo->sem_stop);
			return ;
		}
		sem_post(philo->sem_stop);
		philo->max_think_time = philo->shared_data->time_to_die
			- (philo->shared_data->time_to_eat
				+ philo->shared_data->time_to_sleep) - 10;
		if (philo->max_think_time < 0)
			philo->max_think_time = 0;
		if(eat(philo) == 1)
			return;
	}
}

t_philo create_philos(int id, t_shared_data *shared_data)
{
	t_philo philo;

	char *index;
	philo.id = id;
	philo.stop_sim = 0;
	philo.last_meal_time = shared_data->current_time;
	philo.eat_times = 0;
	philo.shared_data = shared_data;
	index = ft_itoa(id);
	philo.stop = ft_strjoin("/stop",index);
	philo.last_meal = ft_strjoin("/last_meal_time",index);
	sem_unlink(philo.stop);
	sem_unlink(philo.last_meal);
	philo.sem_stop = sem_open(philo.stop,O_CREAT | O_EXCL,0644,1);
	philo.sem_last_meal_time = sem_open(philo.last_meal,O_CREAT | O_EXCL, 0644, 1);
	return philo;
}

void	finalize_simulation(t_philo *philo)
{
	
	// sem_wait(philo->sem_stop);
	// // if( philo->shared_data->stop == 0)
	// // 	pthread_detach(philo->monitor);
	// // else
	//     philo->stop_sim = 1;
	
	// sem_post(philo->sem_stop);
    // printf("fini %d\n",philo->id + 1);
		// pthread_join(philo->monitor, NULL);
		// printf("fini %d\n",philo->id + 1);

		sem_unlink(philo->stop);
		sem_unlink(philo->last_meal);
		exit(0);
		// printf("g%ld\n",get_current_time());
}
