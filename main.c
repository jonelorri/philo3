#include "philo.h"

//todo: cantidad de comidas
//todo: norm

void    smart_sleep(long long time, t_param *param, int nbr)
{
	long long i;

	i = timestamp();
	while (!(*param->is_dead))
	{
		if (time_diff(i, timestamp()) >= time)
			break;
        usleep(50);
	}
}

int ft_usleep(t_philo *philo, long long seconds, int time_to_die) 
{
    long long time;
    long long time_die;
    long long start_time;

    time = 0;
    time_die = time_to_die;
    start_time = timestamp();
    while (time < seconds)
    {
        if (start_time + time_die <= time)
            return 0;
        usleep(50);
        time += 50;
    }
    return 1;
}

int    print_message(void *arg, char type)
{
    t_philo philo;
    t_param *param;

    philo = *(t_philo *)arg;
    param = philo.param;
    pthread_mutex_lock(&param->print);
    if (type == 'f' && *param->is_dead == 0 && param->nbr_philo > *param->total_eat)
    {
        if (time_diff(param->start_time, timestamp()) >= (*philo.last_meal + param->tm_die))
        {
            printf("%d %d Is dead -\n", (*philo.last_meal + param->tm_die), philo.num);
            *param->is_dead = 1;
            pthread_mutex_unlock(&param->print);
            return (0);
        }
        printf("%lld %d Has taken a Fork\n", time_diff(param->start_time, timestamp()), philo.num);
    }
    else if (type == 'e' && *param->is_dead == 0 && param->nbr_philo > *param->total_eat)
    {
        if (time_diff(param->start_time, timestamp()) >= (*philo.last_meal + param->tm_die))
        {
            printf("%d %d Is dead - -\n", (*philo.last_meal + param->tm_die), philo.num);
            *param->is_dead = 1;
            pthread_mutex_unlock(&param->print);
            return (0);
        }
        printf("%lld %d IS EATING\n", time_diff(param->start_time, timestamp()), philo.num);
        *philo.last_meal = time_diff(param->start_time, timestamp());
    }
    else if (type == 's' && *param->is_dead == 0 && param->nbr_philo > *param->total_eat)
    {
        if (time_diff(param->start_time, timestamp()) >= (*philo.last_meal + param->tm_die))
        {
            printf("%d %d Is dead - - -\n", (*philo.last_meal + param->tm_die), philo.num);
            *param->is_dead = 1;
            pthread_mutex_unlock(&param->print);
            return (0);
        }
        printf("%lld %d Is sleeping\n", time_diff(param->start_time, timestamp()), philo.num);
    }
    else if (type == 't' && *param->is_dead == 0 && param->nbr_philo > *param->total_eat)
    {
        if (time_diff(param->start_time, timestamp()) >= (*philo.last_meal + param->tm_die))
        {
            printf("%d %d Is dead +\n", (*philo.last_meal + param->tm_die), philo.num);
            *param->is_dead = 1;
            pthread_mutex_unlock(&param->print);
            return (0);
        }
        printf("%lld %d Is thinking\n", time_diff(param->start_time, timestamp()), philo.num);
    }
    pthread_mutex_unlock(&param->print);
    return (1);
}

void*    routine(void *arg)
{
    t_philo philo;
    t_param *param;

    philo = *(t_philo *)arg;
    param = philo.param;
    while (*param->is_dead == 0 && param->nbr_philo > *param->total_eat)
    {
        if (philo.num % 2 == 0)
            usleep(100);

        // forks
        pthread_mutex_lock(&param->forks[philo.l_fork]);
        if (!print_message(&param->philo[philo.num - 1], 'f'))
        {
            pthread_mutex_unlock(&param->forks[philo.l_fork]);
            return 0;
        }
        pthread_mutex_lock(&param->forks[philo.r_fork]);
        if (!print_message(&param->philo[philo.num - 1], 'f'))
        {
            pthread_mutex_unlock(&param->forks[philo.r_fork]);
            pthread_mutex_unlock(&param->forks[philo.l_fork]);
            return 0;
        }

        // eat    
        if (!print_message(&param->philo[philo.num - 1], 'e'))
        {
            pthread_mutex_unlock(&param->forks[philo.r_fork]);
            pthread_mutex_unlock(&param->forks[philo.l_fork]); 
            return 0;
        }
        smart_sleep(param->tm_eat, param, (philo.num - 1));
        *philo.nbr_meal += 1;
        if (*philo.nbr_meal == param->nbr_eat)
            *param->total_eat += 1;

        pthread_mutex_unlock(&param->forks[philo.l_fork]);
        pthread_mutex_unlock(&param->forks[philo.r_fork]);
    
        // sleep
        smart_sleep(param->tm_sleep, param, (philo.num - 1));
        if (!print_message(&param->philo[philo.num - 1], 's'))
            return 0;

        // think
        if (*param->is_dead == 1 || !print_message(&param->philo[philo.num - 1], 't'))
            return 0;
    }
    return 0;
}

int main(int argc, char *argv[])
{
    t_param     param;

    if (argc != 5 && argc != 6)
    {
        write(1, "Invalid number of arguments\n", 28);
        free(param.is_dead);
        return (0);
    }
    if (ft_init(&param, argv, argc) == 1)
    {
        free(param.total_eat);
        free(param.is_dead);
        return (0);
    }
    param.i = 0;
    param.start_time = timestamp();
    while (param.i < param.nbr_philo)
    {
        param.philo[param.i].num = param.i + 1;
        if (pthread_create(&param.philo[param.i].thread_id, NULL, &routine, &param.philo[param.i]))
            return 1;
        param.i ++;
    }
    param.i = 0;
    while (param.i < param.nbr_philo)
    {
        if (pthread_join(param.philo[param.i].thread_id, NULL))
            return 1;
        free(param.philo[param.i].last_meal);
        free(param.philo[param.i].nbr_meal);
        param.i ++;
    }
	free(param.is_dead);
	free(param.total_eat);
    param.i = -1;
	while (++param.i < param.nbr_philo)
		pthread_mutex_destroy(&(param.forks[param.i]));
    pthread_mutex_destroy(&(param.print));
}