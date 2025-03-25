
#ifndef PHILO_H
#define PHILO_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/time.h>
#include <pthread.h>
typedef struct t_philo
{
    int *forks;
    int last_time_ate;
    pthread_t thread;

}              s_philo;

typedef struct t_fork
{
    pthread_mutex_t mutex;
}              s_fork;
typedef struct t_shared_data
{
    int nb_philos;
    int time_to_die;
    int time_to_eat;
    int time_to_sleep;
}              s_shared_data;
/***********utils */
size_t ft_strlen(char *str);
int *check_argument(int ac,char **av);

#endif