#include "philo.h"

int ft_init(t_param *param, char **argv)
{
    param->nbr_philo = ft_atoi(argv[1]);
    param->tm_die = ft_atoi(argv[2]);
    param->tm_eat = ft_atoi(argv[3]); 
    param->tm_sleep = ft_atoi(argv[4]);
    param->is_dead = malloc(sizeof(int));
    *param->is_dead = 0;
	if (param->nbr_philo < 2)
    {
        printf("0 1 Has taken a Fork\n");
        usleep((param->tm_die) * 1000);
        printf("%d 1 Is dead\n", param->tm_die);
        return (1);  
    }
    if (param->tm_die < 0 || param->tm_eat < 0
		|| param->tm_sleep < 0)
		return (1);
    param->i = param->nbr_philo;
    while (--param->i >= 0)
    {
        if (pthread_mutex_init(&(param->forks[param->i]), NULL))
        {
            printf("Error\n");
            return (1);
        }
    }
    if (pthread_mutex_init(&(param->print), NULL))
    {
        printf("Error\n");
        return (1);
    }
    param->i = param->nbr_philo;
	while (--param->i >= 0)
	{
		param->philo[param->i].id = param->i;
		param->philo[param->i].last_meal = malloc(sizeof(int));
		*param->philo[param->i].last_meal = 0;
		param->philo[param->i].l_fork = param->i;
		param->philo[param->i].r_fork = (param->i + 1) % param->nbr_philo; // 0%5=0 / 1%5=1 / 2%5=2 .../ 5%5=0
		param->philo[param->i].param = param; //enlazo la estructura de dentro con la de fuera
	}
    return (0);
}