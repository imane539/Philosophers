#include "philo.h"

void	init_forks_order(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		philo->first_fork = philo->id;
		philo->second_fork = (philo->id + 1) % philo->shared_data->nb_philos;
	}
	else
	{
		philo->first_fork = (philo->id + 1) % philo->shared_data->nb_philos;
		philo->second_fork = philo->id;
	}
}

long	get_current_time(void)
{
	static struct timeval	start;
	static int				first_time;
	struct timeval			current_time;

	if (!first_time)
	{
		gettimeofday(&start, NULL);
		first_time = 1;
	}
	gettimeofday(&current_time, NULL);
	return (((current_time.tv_sec - start.tv_sec) * 1000)
		+ ((current_time.tv_usec - start.tv_usec) / 1000));
}

size_t	ft_strlen(char *str)
{
	size_t	i;

	i = 0;
	if (!str)
		return (i);
	while (str[i])
		i++;
	return (i);
}

long	ft_atoi(const char *str, int *error)
{
	int		i;
	int		sign;
	long	num;
	int		count;

	count = 0;
	i = 0;
	sign = 1;
	num = 0;
	while (str[i] && (str[i] == '-' || str[i] == '+') && count < 1)
	{
		count++;
		if (str[i] == '-')
			sign *= -1;
		i++;
	}
	while (str[i] && str[i] >= 48 && str[i] <= 57)
		num = (num * 10) + str[i++] - 48;
	if (str[i] && (str[i] < 48 || str[i] > 57))
	{
		*error = 1;
	}
	return (num * sign);
}

int	*check_argument(int ac, char **av)
{
	long	value;
	int		*num;

	int (i), (error), (j);
	i = 1;
	value = 0;
	j = 0;
	error = 0;
	num = malloc(sizeof(int) * (ac - 1));
	while (i < ac)
	{
		value = ft_atoi(av[i], &error);
		if (error == 1 || value > 2147483647 || value < 0)
		{
			printf("invalid number:%s\n", av[i]);
			free(num);
			return (NULL);
		}
		num[j++] = value;
		i++;
	}
	return (num);
}
