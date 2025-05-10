#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>


typedef struct s_shared_data
{
	int				nb_philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	long			current_time;
	pthread_mutex_t	*mutex_forks;
	int				stop;
	int				max_eats;
	int				dead_philo;
	pthread_mutex_t	mtx_print;
	pthread_mutex_t	die;
}					t_shared_data;
typedef struct s_philo
{
	int				id;
	pthread_t		thread;
	t_shared_data	*shared_data;
	long			last_meal_time;
	int				first_fork;
	int				second_fork;
	int				eat_times;
	int				max_think_time;
	pthread_mutex_t	eat_times_mutex;
	pthread_mutex_t	last_meal_time_mutex;
}					t_philo;

/***********utils ***********/
size_t				ft_strlen(char *str);
long				ft_atoi(const char *str, int *error);
int					*check_argument(int ac, char **av);
long				get_current_time(void);
void				init_forks_order(t_philo *philo);
/***********monitor ***********/
int					verify_meal_completion(t_philo *philos);
void				*monitor(void *arg);
int					detect_death(t_philo *philos, int i);

/************philo_manager*** */
void				eat(t_philo *philo);
void				*philosopher(void *data);
t_philo				*create_philos(t_philo *philos, t_shared_data *shared_data);
void				finalize_simulation(t_philo *philos,
						t_shared_data *shared_data, pthread_t monitor_thread);

/*************philo********* */

void ft_usleep(unsigned int usec);
void				mutex_print(t_shared_data *shared_data, char *msg, int id,
						char check);
void				fill_shared_data(t_shared_data *shared_data, int *num);

#endif