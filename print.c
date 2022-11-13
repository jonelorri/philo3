/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jelorria <jelorria@student.42urduli>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 19:12:00 by jelorria          #+#    #+#             */
/*   Updated: 2022/11/11 19:12:02 by jelorria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_dead(void *arg)
{
	t_philo	ph;
	t_p		*p;

	ph = *(t_philo *)arg;
	p = ph.p;
	if (time_diff(p->tm_1, timestamp()) >= (*ph.last_meal + p->tm_die))
	{
		printf("\033[0;31m");
		printf("%d %d Is dead\n", (*ph.last_meal + p->tm_die), ph.num);
		printf("\033[0m");
		*p->is_dead = 1;
		pthread_mutex_unlock(&p->print);
		return (0);
	}
	return (1);
}

void	print_eat(long long time, int ph_num)
{
	printf("\033[0;32m");
	printf("%lld %d Is eating\n", time, ph_num);
	printf("\033[0m");
}

int	printing(void *arg, char type)
{
	t_philo	ph;
	t_p		*p;

	ph = *(t_philo *)arg;
	p = ph.p;
	if (type == 'e' && *p->is_dead == 0 && p->n_ph > *p->total_eat)
	{
		if (!check_dead(&p->ph[ph.num - 1]))
			return (0);
		print_eat(time_diff(p->tm_1, timestamp()), ph.num);
		*ph.last_meal = time_diff(p->tm_1, timestamp());
	}
	else if (type == 's' && *p->is_dead == 0 && p->n_ph > *p->total_eat)
	{
		if (!check_dead(&p->ph[ph.num - 1]))
			return (0);
		printf("%lld %d Is sleeping\n", time_diff(p->tm_1, timestamp()), ph.num);
	}
	else if (type == 't' && *p->is_dead == 0 && p->n_ph > *p->total_eat)
	{
		if (!check_dead(&p->ph[ph.num - 1]))
			return (0);
		printf("%lld %d Is thinking\n", time_diff(p->tm_1, timestamp()), ph.num);
	}
	return (1);
}

int	print_message(void *arg, char type)
{
	t_philo	ph;
	t_p		*p;

	ph = *(t_philo *)arg;
	p = ph.p;
	pthread_mutex_lock(&p->print);
	if (type == 'f' && *p->is_dead == 0 && p->n_ph > *p->total_eat)
	{
		if (!check_dead(&p->ph[ph.num - 1]))
			return (0);
		printf("%lld %d", time_diff(p->tm_1, timestamp()), ph.num);
		printf(" Has taken a Fork\n");
	}
	else
	{
		if (!printing(&p->ph[ph.num - 1], type))
			return (0);
	}
	pthread_mutex_unlock(&p->print);
	return (1);
}
