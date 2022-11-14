/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jelorria <jelorria@student.42urduli>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 16:17:38 by jelorria          #+#    #+#             */
/*   Updated: 2022/11/14 16:17:40 by jelorria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	routine_init(void *arg)
{
	t_philo	ph;
	t_p		*p;

	ph = *(t_philo *)arg;
	p = ph.p;
	if (ph.num % 2 == 0)
		usleep(100);
	pthread_mutex_lock(&p->forks[ph.l_fork]);
}

int	routine_fork1(void *arg)
{
	t_philo	ph;
	t_p		*p;

	ph = *(t_philo *)arg;
	p = ph.p;
	routine_init(&ph);
	if (!print_message(&p->ph[ph.num - 1], 'f'))
	{
		pthread_mutex_unlock(&p->forks[ph.l_fork]);
		return (0);
	}
	pthread_mutex_lock(&p->forks[ph.r_fork]);
	if (!print_message(&p->ph[ph.num - 1], 'f'))
	{
		pthread_mutex_unlock(&p->forks[ph.r_fork]);
		pthread_mutex_unlock(&p->forks[ph.l_fork]);
		return (0);
	}
	if (!print_message(&p->ph[ph.num - 1], 'e'))
	{
		pthread_mutex_unlock(&p->forks[ph.r_fork]);
		pthread_mutex_unlock(&p->forks[ph.l_fork]);
		return (0);
	}
	return (1);
}

void	*routine(void *arg)
{
	t_philo	ph;
	t_p		*p;

	ph = *(t_philo *)arg;
	p = ph.p;
	while (*p->is_dead == 0 && p->n_ph > *p->total_eat)
	{
		if (!routine_fork1(&ph))
			return (0);
		smart_sleep(p->tm_eat, p);
		*ph.nbr_meal += 1;
		if (*ph.nbr_meal == p->nbr_eat)
			*p->total_eat += 1;
		pthread_mutex_unlock(&p->forks[ph.l_fork]);
		pthread_mutex_unlock(&p->forks[ph.r_fork]);
		if (ph.num % 2 == 0)
			smart_sleep(p->tm_sleep, p);
		if (!print_message(&p->ph[ph.num - 1], 's'))
			return (0);
		if (ph.num % 2 != 0)
			smart_sleep(p->tm_sleep, p);
		if (*p->is_dead == 1 || !print_message(&p->ph[ph.num - 1], 't'))
			return (0);
	}
	return (0);
}

int	start(int argc, char **argv, t_p *p)
{
	if (argc != 5 && argc != 6)
	{
		printf("Invalid number of arguments\n");
		free(p->is_dead);
		return (0);
	}
	if (ft_init(p, argv, argc) == 1)
	{
		free(p->total_eat);
		free(p->is_dead);
		return (0);
	}
	p->i = 0;
	p->tm_1 = timestamp();
	while (p->i < p->n_ph)
	{
		p->ph[p->i].num = p->i + 1;
		if (pthread_create(&p->ph[p->i].th_id, NULL, &routine, &p->ph[p->i]))
			return (1);
		p->i ++;
	}
	return (1);
}

int	main(int argc, char *argv[])
{
	t_p	p;

	if (!start(argc, argv, &p))
		return (0);
	p.i = 0;
	while (p.i < p.n_ph)
	{
		if (pthread_join(p.ph[p.i].th_id, NULL))
			return (1);
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
