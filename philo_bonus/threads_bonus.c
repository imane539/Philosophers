#include "philo_bonus.h"
void *detect_death(void *arg)
{
	t_philo *philo;
    int i ;
    i = 0;
	philo = (t_philo *)arg;
    while(1)
    {
        sem_wait(philo->sem_last_meal_time);
        if (get_current_time()
            - philo->last_meal_time > philo->shared_data->time_to_die)
        {
            // printf("wax nta %d\n",philo->id + 1);
            // printf("ana lwl %d %ld\n",philo->id + 1,get_current_time());
            sem_post(philo->sem_last_meal_time);
            sem_wait(philo->shared_data->die);
            sem_wait(philo->sem_stop);
            // printf("fink %d\n",philo->id + 1);
            if(philo->stop_sim == 1)
            {
            // printf("ana hna %d\n",philo->id + 1);

    	    	sem_post(philo->sem_stop);
                sem_post(philo->shared_data->die);
                return NULL;
            } 
            philo->stop_sim = 1;
    		sem_post(philo->sem_stop); 
            // printf("ana lwl %d\n",philo->id + 1);
            while(i < philo->shared_data->nb_philos )
            {
                sem_post(philo->shared_data->block);
                i++;
            }
	        sema_print(philo, "died", philo->id , 'm');
            finalize_simulation(philo);

            // sem_post(philo->shared_data->die); 
            return NULL;
        }
        sem_post(philo->sem_last_meal_time);
		ft_usleep(1000);
    }
}


void *death_blocker(void *arg)
{
    t_philo *philo;
	philo = (t_philo *)arg; 
    int i;
    i = 0;
    sem_wait(philo->shared_data->block);
    sem_wait(philo->sem_stop);
    if(philo->stop_sim == 1)
    {
        sem_post(philo->sem_stop);
        return NULL;    
    }
    philo->stop_sim = 1;
    sem_post(philo->sem_stop);
    finalize_simulation(philo);
    return NULL;
}
