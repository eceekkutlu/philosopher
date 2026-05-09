#include "plo.h"
#include <stdio.h>
#include <unistd.h>

void create_philo(t_philo *philo,int must)
{
    int i;

    i = 0;
    while(i < must)
    {
        pthread_create(&philo[i].thread, NULL, routine, &philo[i]);
        i++;

    }
}

int create_fork(t_table *table)
{
    int i;
    int result;
    
    i = 0;
    //structtaki idler verdik
    while(i < table->philo_count)
    {
        table->fork[i].id = i;
        //mutex init 
        result = pthread_mutex_init(&table->fork[i].mutex,NULL);
        if(result != 0)
        // mutexle kilitleme yapıyoruz neden ? -> çatalın anlık kullanımda olduğunu ifade ediyor 
            return 1;
        i++;
    }
    return 0;
    // forklara i bilgini verdim.
}

void init_philo(t_philo *philo,t_table *table)
{
    int i ;
    i = 0;
    while(i < table->philo_count)
    {
        philo[i].table = table;
        philo[i].id = i + 1;
        philo[i].last_meal = table->start;
        philo[i].left_fork = &table->fork[i];
        if(i == (table->philo_count)-1)
        {
            philo[i].right_fork = &table->fork[0];
        }
        else
            philo[i].right_fork = &table->fork[i+1];
        i++;
    }
}
void fork_for_philo(t_philo *philo)
{
    t_fork *first;
    t_fork *second;
    if(philo->id%2==0)
    {
        first = philo->right_fork;
        second = philo -> left_fork;
    }
    else
    {
        first = philo->left_fork;
        second = philo -> right_fork;
    }
    pthread_mutex_lock(&first->mutex);
    safe_print(philo, "has taken a fork");

    pthread_mutex_lock(&second->mutex);
    safe_print(philo, "has taken a fork");
}

void *routine(void *arg)
{
    t_philo *philo;

    philo = (t_philo *)arg;
    if (philo->table->philo_count == 1)
    {
        pthread_mutex_lock(&philo->left_fork->mutex);
        safe_print(philo, "has taken a fork");
        while (is_dead(philo->table) == 0)
            usleep(500);
        pthread_mutex_unlock(&philo->left_fork->mutex);
        return (NULL);
    }
    while(is_dead(philo->table) == 0)
    {
        fork_for_philo(philo);
        for_eating(philo);
        unlock_fork(philo);
        for_sleeping(philo);
        for_thinking(philo);
    }
    return NULL;
}// her filozof yaşam döngüsünü burada oluşturdu.

