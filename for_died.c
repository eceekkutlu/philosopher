/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   for_died.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkutlu <zkutlu@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/03 23:44:59 by zkutlu            #+#    #+#             */
/*   Updated: 2026/07/04 05:53:52 by zkutlu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	last_process_philo(t_philo *philo)
{
	long	last;

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

void	detection_died_utils(t_philo *philo)
{
	int		i;
	long	death_time;

	i = 0;
	while (i < philo->table->philo_count)
	{
		if (last_process_philo(&philo[i]) > philo->table->die)
		{
			death_time = get_time_ms() - philo->table->start;
			set_dead(philo->table);
			pthread_mutex_lock(&philo->table->print_lock);
			printf("%ld %d died\n", death_time, philo[i].id);
			pthread_mutex_unlock(&philo->table->print_lock);
			return ;
		}
		i++;
	}
}

void	detection_died(t_philo *philo)
{
	int	i;

	while (is_dead(philo->table) == 0)
	{
		detection_died_utils(philo);
		if (philo->table->must_eat > 0)
		{
			pthread_mutex_lock(&philo->table->state_lock);
			i = 0;
			while (i < philo->table->philo_count
				&& philo[i].meals_eaten >= philo->table->must_eat)
				i++;
			pthread_mutex_unlock(&philo->table->state_lock);
			if (i == philo->table->philo_count)
			{
				set_dead(philo->table);
				return ;
			}
		}
		usleep(1000);
	}
}
