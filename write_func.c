#include "plo.h"
#include <stdio.h>
#include <unistd.h>

void safe_print(t_philo *philo, char *msg)
{
    is_safe(philo, msg);
}

void is_safe(t_philo *philo,char *str)
{
        long elapsed;
        long current;

        current = get_time_ms();
        elapsed= current - philo->table->start;

        pthread_mutex_lock(&philo->table->print_lock);
        printf("%ld %d %s", elapsed, philo->id, str);
        pthread_mutex_unlock(&philo->table->print_lock);
}
void for_eating(t_philo *philo)
{
    set_meal(philo);
    safe_print(philo, "is eating");
    usleep(philo->table->eat * 1000);
    //usleep mikrosaniye ister
    //milisaniyeye çevirdik
}
void for_thinking(t_philo *philo)
{
    safe_print(philo, "is thinking");
    usleep(philo->table->think * 1000);
    //usleep mikrosaniye ister
    //milisaniyeye çevirdik
}
void for_sleeping(t_philo *philo)
{
    safe_print(philo, "is sleeping");
    usleep(philo->table->sleep * 1000);
    //usleep mikrosaniye ister
    //milisaniyeye çevirdik
}