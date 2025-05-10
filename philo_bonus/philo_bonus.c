#include "philo_bonus.h"
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
int sema_print(t_philo *philo, char *msg, int id, char check)
{
	if (check == 'm')
	{
		sem_wait(philo->shared_data->print);
		printf("%ld %d %s\n", get_current_time(), id + 1, msg);
		return 0;
	}
	// printf("==============block %s%d\n",msg,philo->id + 1);
	sem_wait(philo->sem_stop);
	if (philo->stop_sim != 0)
	{
	// printf("blocka%d\n",philo->id + 1);

		sem_post(philo->sem_stop);
		return 1;
	}
	// printf("aftblocka%d\n",philo->id + 1);

	// printf("blocka%d\n",philo->id);
	// printf("sb9tk,%d\n",philo->id + 1);

	// printf("%d\n",philo->stop_sim);
	sem_post(philo->sem_stop);
	sem_wait(philo->shared_data->print);
	printf("%ld %d %s\n", get_current_time(), id + 1, msg);
	sem_post(philo->shared_data->print);
	return 0;
}
void	fill_shared_data(t_shared_data *shared_data, int *num)
{
	int	i;
	i = 0;
	shared_data->nb_philos = num[0];
	shared_data->time_to_die = num[1];
	shared_data->time_to_eat = num[2];
	shared_data->time_to_sleep = num[3];
	shared_data->dead_philo = 0;
	shared_data->current_time = get_current_time();
	sem_unlink("/forks");
	sem_unlink("/block");
	sem_unlink("/die");
	sem_unlink("/print");
	shared_data->sem = sem_open("/forks",O_CREAT | O_EXCL,0644,shared_data->nb_philos);
	shared_data->block = sem_open("/block",O_CREAT | O_EXCL,0644,0);
	shared_data->die = sem_open("/die",O_CREAT | O_EXCL,0644,1);
	shared_data->print = sem_open("/print",O_CREAT | O_EXCL,0644,1);
}
void	parent( t_shared_data *shared_data)
{
	t_philo			philo;
	int i;
	int id;
	i = 0;
	shared_data->id_P = malloc(sizeof(int) * shared_data->nb_philos);
	while(i < shared_data->nb_philos)
	{
		id = fork();
		if(id == 0)
		{
			philo = create_philos(i,shared_data);
			philosopher(&philo);

		}
		else
		{
			shared_data->id_P[i] = id;
			i++;
		}
	}
}
int	main(int ac, char **av)
{
	int				*num;
	t_shared_data	shared_data;
	int	(i);
	i = 0;
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
	parent(&shared_data);
	while(i < shared_data.nb_philos)
		waitpid(shared_data.id_P[i++], NULL, 0);
	free(shared_data.id_P);
	sem_unlink("/forks");
	sem_unlink("/block");
	sem_unlink("/print");
	sem_unlink("/die");

}
