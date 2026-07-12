/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_func.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkutlu <zkutlu@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/03 23:44:19 by zkutlu            #+#    #+#             */
/*   Updated: 2026/07/03 23:52:50 by zkutlu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
	think_time = (philo->table->die - (get_time_ms() - last)
			- philo->table->eat) / 2;
	if (think_time < 0)
		think_time = 0;
	if (think_time > 600)
		think_time = 200;
	if (philo->table->philo_count % 2 != 0)
		think_time += 1;
	usleep(think_time * 1000);
}

void	for_sleeping(t_philo *philo)
{
	safe_print(philo, "is sleeping");
	usleep(philo->table->sleep * 1000);
}

int	arg_control(t_table *table, int *n, int argc, char **argv)
{
	int	must_eat;

	if (argc != 5 && argc != 6)
	{
		printf("error\n");
		return (1);
	}
	if (!parse_positive_int(argv[1], n) || !parse_positive_int(argv[2],
			&table->die) || !parse_positive_int(argv[3], &table->eat)
		|| !parse_positive_int(argv[4], &table->sleep))
	{
		printf("error\n");
		return (1);
	}
	table->must_eat = -1;
	if (argc == 6)
	{
		if (!parse_positive_int(argv[5], &must_eat))
			return (printf("error\n"), 1);
		table->must_eat = must_eat;
	}
	return (0);
}
