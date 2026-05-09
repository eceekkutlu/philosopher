#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>

typedef struct s_fork t_fork;
typedef struct s_table t_table;
typedef struct s_philo t_philo;

typedef struct s_fork
{
    int             id;
    pthread_mutex_t mutex;
}   t_fork;

typedef struct s_table
{
    int             philo_count;
    int             die;
    int             eat;
    int             sleep;
    int             died;
    int             think;
    long            start;

    t_fork         *fork;

    pthread_mutex_t print_lock;
    pthread_mutex_t state_lock;
}   t_table;

typedef struct s_philo
{
    int             id;
    long            last_meal;

    pthread_t       thread;
    t_fork         *left_fork;
    t_fork         *right_fork;

    t_table        *table;
}   t_philo;

void    create_philo(t_philo *philo, int must);
int     create_fork(t_table *table);
void    init_philo(t_philo *philo, t_table *table);
void    fork_for_philo(t_philo *philo);
void    unlock_fork(t_philo *philo);
void    is_safe(t_philo *philo, char *str);
void    for_eating(t_philo *philo);
void    for_thinking(t_philo *philo);
void    for_sleeping(t_philo *philo);
void   *routine(void *arg);
void    safe_print(t_philo *philo, char *msg);
void    join_threads(t_philo *philo);
long    last_process_philo(t_philo *philo);
long    get_time_ms(void);
int     is_dead(t_table *table);
void    set_dead(t_table *table);
void    set_meal(t_philo *philo);
void    detection_died(t_philo *philo);

#endif