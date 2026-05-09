#include "plo.h"
#include <stddef.h>
#include <sys/time.h>

long get_time_ms(void)
{
    struct timeval  time_now;

    gettimeofday(&time_now, NULL);
    return (time_now.tv_sec * 1000L + time_now.tv_usec / 1000);
}

void join_threads(t_philo *philo)
{
	int i;

	i = 0;
	while (i < philo->table->philo_count)
	{
		pthread_join(philo[i].thread, NULL);
		i++;
	}
}

void unlock_fork(t_philo *philo)
{
	pthread_mutex_unlock(&philo->left_fork->mutex);
	pthread_mutex_unlock(&philo->right_fork->mutex);
}

void	set_meal(t_philo *philo)
{

	pthread_mutex_lock(&philo->table->state_lock);
	philo->last_meal = get_time_ms();
	pthread_mutex_unlock(&philo->table->state_lock);
}