#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

 #include <fcntl.h>   
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>
# include <semaphore.h>
#include <sys/wait.h>
#include <pthread.h>

typedef struct s_shared_data
{
	int				nb_philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	long			current_time;
	int				*forks;
	int				max_eats;
	int				dead_philo;
	sem_t 			*sem;
	sem_t 			*block;
	sem_t 			*die;
	sem_t 			*print;
	int				*id_P;
}					t_shared_data;
typedef struct s_philo
{
	int				id;
	int				stop_sim;
	t_shared_data	*shared_data;
	long			last_meal_time;
	int				eat_times;
	int				max_think_time;
	pthread_t		monitor;
	pthread_t		death_blocker;
	sem_t 			*sem_stop;
	sem_t			*sem_last_meal_time;
	char			*stop;
	char			*last_meal;
}					t_philo;

/***********utils ***********/
size_t				ft_strlen(char *str);
long				ft_atoi(const char *str, int *error);
int					*check_argument(int ac, char **av);
long				get_current_time(void);
char	*ft_strjoin(char  *s1, char  *s2);

/************itoa********* */
char	*ft_strdup( char *s1);
char	*alloc(int j, int sign);
char	*fill(int n, int sign);
char	*ft_itoa(int n);
/************philo_manager*** */
int				eat(t_philo *philo);
void				philosopher(t_philo	*philo);
t_philo create_philos(int id, t_shared_data *shared_data);
void	finalize_simulation(t_philo *philo);

/*************philo********* */
void ft_usleep(unsigned int usec);
int	sema_print(t_philo *philo, char *msg, int id, char check);
void				fill_shared_data(t_shared_data *shared_data, int *num);


/*************threads********* */
void *death_blocker(void *arg);
void *detect_death(void *arg);
#endif