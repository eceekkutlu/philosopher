#include "plo.h"
#include <stdio.h>
#include <unistd.h>

void	safe_print(t_philo *philo, char *msg)
{
	long	elapsed;

	if (is_dead(philo->table))
		return ;
	elapsed = get_time_ms() - philo->table->start;
	pthread_mutex_lock(&philo->table->print_lock);
	if (!is_dead(philo->table))
		printf("%ld %d %s\n", elapsed, philo->id, msg);
	pthread_mutex_unlock(&philo->table->print_lock);
}

void	for_eating(t_philo *philo)
{
	set_meal(philo);
	safe_print(philo, "is eating");
	usleep(philo->table->eat * 1000);
}

void	for_thinking(t_philo *philo)
{
	long	last;
	long	think_time;

	safe_print(philo, "is thinking");
	pthread_mutex_lock(&philo->table->state_lock);
	last = philo->last_meal;
	pthread_mutex_unlock(&philo->table->state_lock);
	think_time = (philo->table->die
			- (get_time_ms() - last)
			- philo->table->eat) / 2;
	if (think_time < 0)
		think_time = 0;
	if (think_time > 600)
		think_time = 200;
	usleep(think_time * 1000);
}

void	for_sleeping(t_philo *philo)
{
	safe_print(philo, "is sleeping");
	usleep(philo->table->sleep * 1000);
}
