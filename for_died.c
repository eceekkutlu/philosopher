#include "plo.h"
#include <stddef.h>
#include <sys/time.h>
#include <unistd.h>
long last_process_philo(t_philo *philo)
{
    long last;

    pthread_mutex_lock(&philo->table->state_lock);
    last = philo->last_meal;
    pthread_mutex_unlock(&philo->table->state_lock);

    return (get_time_ms() - last);
}
int	is_dead(t_table *table)
{
	int	dead;

	pthread_mutex_lock(&table->state_lock);
	dead = table->died;
	pthread_mutex_unlock(&table->state_lock);
	return (dead);
}
void	set_dead(t_table *table)
{
	pthread_mutex_lock(&table->state_lock);
	table->died = 1;
	pthread_mutex_unlock(&table->state_lock);
}
void detection_died(t_philo *philo)
{
    int i;

    while (is_dead(philo->table) == 0)
    {
        i = 0;
        while (i < philo->table->philo_count)
        {
            if (last_process_philo(&philo[i]) > philo->table->die)
            {
                set_dead(philo->table);
                is_safe(&philo[i], "died");
                return;
            }
            i++;
        }
        usleep(1000);
    }
}
