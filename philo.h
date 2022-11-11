#ifndef PHILO_H
# define PHILO_H

#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/time.h>

typedef struct  s_philo
{
    pthread_t       thread_id;
    int             id;
    int             num;
    int             l_fork;
    int             r_fork;
    int             *last_meal;
    int             *nbr_meal;
    struct s_param  *param;
}                   t_philo;

typedef struct  s_param
{
    int             nbr_philo;
    int             tm_die;
    int             tm_eat;
    int             tm_sleep;
    int             nbr_eat;
    int             *total_eat;
    int             *is_dead;
    int             i;
    long long       start_time;
    t_philo         philo[200];
    pthread_mutex_t forks[200];
    pthread_mutex_t print;
}                   t_param;

int         ft_init(t_param *param, char **argv, int argc);
int 	    ft_atoi(const char *str);
long long   timestamp(void);
long long	time_diff(long long past, long long pres);
int         execute(t_param *param);
char	    *ft_itoa(int n);
int         print_message(void *arg, char type);

#endif