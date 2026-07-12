/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_func.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkutlu <zkutlu@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/03 23:45:41 by zkutlu            #+#    #+#             */
/*   Updated: 2026/07/04 05:26:08 by zkutlu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	create_philo(t_philo *philo, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		pthread_create(&philo[i].thread, NULL, routine, &philo[i]);
		i++;
	}
}

int	create_fork(t_table *table)
{
	int	i;
	int	result;

	i = 0;
	while (i < table->philo_count)
	{
		table->fork[i].id = i;
		result = pthread_mutex_init(&table->fork[i].mutex, NULL);
		if (result != 0)
			return (1);
		i++;
	}
	return (0);
}

void	init_philo(t_philo *philo, t_table *table)
{
	int	i;

	i = 0;
	while (i < table->philo_count)
	{
		philo[i].table = table;
		philo[i].id = i + 1;
		philo[i].meals_eaten = 0;
		philo[i].last_meal = table->start;
		philo[i].left_fork = &table->fork[i];
		if (i == table->philo_count - 1)
			philo[i].right_fork = &table->fork[0];
		else
			philo[i].right_fork = &table->fork[i + 1];
		i++;
	}
}

void	fork_for_philo(t_philo *philo)
{
	t_fork	*first;
	t_fork	*second;

	if (philo->id % 2 == 0)
	{
		first = philo->right_fork;
		second = philo->left_fork;
	}
	else
	{
		first = philo->left_fork;
		second = philo->right_fork;
	}
	pthread_mutex_lock(&first->mutex);
	safe_print(philo, "has taken a fork");
	pthread_mutex_lock(&second->mutex);
	safe_print(philo, "has taken a fork");
}

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->id % 2 == 0)
		usleep(1000);
	if (philo->table->philo_count == 1)
	{
		pthread_mutex_lock(&philo->left_fork->mutex);
		safe_print(philo, "has taken a fork");
		while (is_dead(philo->table) == 0)
			usleep(500);
		pthread_mutex_unlock(&philo->left_fork->mutex);
		return (NULL);
	}
	while (is_dead(philo->table) == 0)
	{
		fork_for_philo(philo);
		for_eating(philo);
		unlock_fork(philo);
		for_sleeping(philo);
		for_thinking(philo);
	}
	return (NULL);
}
