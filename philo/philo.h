/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkutlu <zkutlu@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/03 23:46:12 by zkutlu            #+#    #+#             */
/*   Updated: 2026/07/04 05:33:00 by zkutlu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <ctype.h>
# include <errno.h>
# include <limits.h>
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_fork
{
	int					id;
	pthread_mutex_t		mutex;
}						t_fork;

typedef struct s_table
{
	int					philo_count;
	int					die;
	int					eat;
	int					sleep;
	int					must_eat;
	int					died;
	long				start;

	t_fork				*fork;

	pthread_mutex_t		print_lock;
	pthread_mutex_t		state_lock;
}						t_table;

typedef struct s_philo
{
	int			id;
	int			meals_eaten;
	long		last_meal;
	pthread_t	thread;
	t_fork		*left_fork;
	t_fork		*right_fork;
	t_table		*table;
}				t_philo;

void	create_philo(t_philo *philo, int count);
int		create_fork(t_table *table);
void	init_philo(t_philo *philo, t_table *table);
void	fork_for_philo(t_philo *philo);
void	unlock_fork(t_philo *philo);
void	for_eating(t_philo *philo);
void	for_thinking(t_philo *philo);
void	for_sleeping(t_philo *philo);
void	*routine(void *arg);
void	safe_print(t_philo *philo, char *msg);
void	join_threads(t_philo *philo);
long	last_process_philo(t_philo *philo);
long	get_time_ms(void);
int		is_dead(t_table *table);
void	set_dead(t_table *table);
void	set_meal(t_philo *philo);
void	detection_died(t_philo *philo);
int		arg_control(t_table *table, int *n,
			int argc, char **argv);
int		parse_positive_int(char *str, int *out);

#endif
