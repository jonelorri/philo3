#include "philo.h"

void*    routine(void *arg)
{
	t_philo ph;
	t_p *p;

	ph = *(t_philo *)arg;
	p = ph.p;
	while (*p->is_dead == 0 && p->n_ph > *p->total_eat)
	{
		if (ph.num % 2 == 0)
			usleep(100);
		pthread_mutex_lock(&p->forks[ph.l_fork]);
		if (!print_message(&p->ph[ph.num - 1], 'f'))
		{
			pthread_mutex_unlock(&p->forks[ph.l_fork]);
			return 0;
		}
		pthread_mutex_lock(&p->forks[ph.r_fork]);
		if (!print_message(&p->ph[ph.num - 1], 'f'))
		{
			pthread_mutex_unlock(&p->forks[ph.r_fork]);
			pthread_mutex_unlock(&p->forks[ph.l_fork]);
			return 0;
		}
		if (!print_message(&p->ph[ph.num - 1], 'e'))
		{
			pthread_mutex_unlock(&p->forks[ph.r_fork]);
			pthread_mutex_unlock(&p->forks[ph.l_fork]); 
			return 0;
		}
		smart_sleep(p->tm_eat, p, (ph.num - 1));
		*ph.nbr_meal += 1;
		if (*ph.nbr_meal == p->nbr_eat)
			*p->total_eat += 1;
		pthread_mutex_unlock(&p->forks[ph.l_fork]);
		pthread_mutex_unlock(&p->forks[ph.r_fork]);
		smart_sleep(p->tm_sleep, p, (ph.num - 1));
		if (!print_message(&p->ph[ph.num - 1], 's'))
			return 0;
		if (*p->is_dead == 1 || !print_message(&p->ph[ph.num - 1], 't'))
			return 0;
	}
	return 0;
}

int main(int argc, char *argv[])
{
	t_p	p;

	if (argc != 5 && argc != 6)
	{
		write(1, "Invalid number of arguments\n", 28);
		free(p.is_dead);
		return (0);
	}
	if (ft_init(&p, argv, argc) == 1)
	{
		free(p.total_eat);
		free(p.is_dead);
		return (0);
	}
	p.i = 0;
	p.tm_1 = timestamp();
	while (p.i < p.n_ph)
	{
		p.ph[p.i].num = p.i + 1;
		if (pthread_create(&p.ph[p.i].thread_id, NULL, &routine, &p.ph[p.i]))
			return 1;
		p.i ++;
	}
	p.i = 0;
	while (p.i < p.n_ph)
	{
		if (pthread_join(p.ph[p.i].thread_id, NULL))
			return 1;
		free(p.ph[p.i].last_meal);
		free(p.ph[p.i].nbr_meal);
		p.i ++;
	}
	free(p.is_dead);
	free(p.total_eat);
	p.i = -1;
	while (++p.i < p.n_ph)
		pthread_mutex_destroy(&(p.forks[p.i]));
	pthread_mutex_destroy(&(p.print));
}