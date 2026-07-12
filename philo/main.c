/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkutlu <zkutlu@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/03 23:40:13 by zkutlu            #+#    #+#             */
/*   Updated: 2026/07/03 23:40:13 by zkutlu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	is_positive_number(char *str)
{
	int	i;

	i = 0;
	if (!str || str[0] == '\0')
		return (0);
	while (str[i])
	{
		if (!isdigit((unsigned char)str[i]))
			return (0);
		i++;
	}
	return (1);
}

int	parse_positive_int(char *str, int *out)
{
	long	value;
	char	*end_ptr;

	if (!is_positive_number(str))
		return (0);
	errno = 0;
	value = strtol(str, &end_ptr, 10);
	if (errno != 0 || *end_ptr != '\0')
		return (0);
	if (value <= 0 || value > INT_MAX)
		return (0);
	*out = (int)value;
	return (1);
}

static int	init_table(t_table *table, t_philo **philo, int n)
{
	table->philo_count = n;
	table->died = 0;
	table->start = get_time_ms();
	table->fork = malloc(sizeof(t_fork) * n);
	if (!table->fork)
		return (1);
	*philo = malloc(sizeof(t_philo) * n);
	if (!*philo)
	{
		free(table->fork);
		return (1);
	}
	pthread_mutex_init(&table->print_lock, NULL);
	pthread_mutex_init(&table->state_lock, NULL);
	if (create_fork(table))
	{
		pthread_mutex_destroy(&table->print_lock);
		pthread_mutex_destroy(&table->state_lock);
		free(*philo);
		free(table->fork);
		return (1);
	}
	return (0);
}

static void	cleanup_table(t_table *table, t_philo *philo)
{
	int	i;

	pthread_mutex_destroy(&table->print_lock);
	pthread_mutex_destroy(&table->state_lock);
	i = 0;
	while (i < table->philo_count)
	{
		pthread_mutex_destroy(&table->fork[i].mutex);
		i++;
	}
	free(philo);
	free(table->fork);
}

int	main(int argc, char **argv)
{
	t_table	table;
	t_philo	*philo;
	int		n;

	if (arg_control(&table, &n, argc, argv))
		return (1);
	if (init_table(&table, &philo, n))
	{
		printf("fork init failed\n");
		return (1);
	}
	init_philo(philo, &table);
	reset_meal_times(philo);
	create_philo(philo, n);
	detection_died(philo);
	join_threads(philo);
	cleanup_table(&table, philo);
	return (0);
}
