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

int	print_message(void *arg, char type)
{
	t_philo	ph;
	t_p		*p;

	ph = *(t_philo *)arg;
	p = ph.p;
	pthread_mutex_lock(&p->print);
	if (type == 'f' && *p->is_dead == 0 && p->n_ph > *p->total_eat)
	{
		if (time_diff(p->tm_1, timestamp()) >= (*ph.last_meal + p->tm_die))
		{
			printf("%d %d Is dead\n", (*ph.last_meal + p->tm_die), ph.num);
			*p->is_dead = 1;
			pthread_mutex_unlock(&p->print);
			return (0);
		}
		printf("%lld %d Has taken a Fork\n", time_diff(p->tm_1, timestamp()), ph.num);
	}
	else if (type == 'e' && *p->is_dead == 0 && p->n_ph > *p->total_eat)
	{
		if (time_diff(p->tm_1, timestamp()) >= (*ph.last_meal + p->tm_die))
		{
			printf("%d %d Is dead\n", (*ph.last_meal + p->tm_die), ph.num);
			*p->is_dead = 1;
			pthread_mutex_unlock(&p->print);
			return (0);
		}
		printf("%lld %d IS EATING\n", time_diff(p->tm_1, timestamp()), ph.num);
		*ph.last_meal = time_diff(p->tm_1, timestamp());
	}
	else if (type == 's' && *p->is_dead == 0 && p->n_ph > *p->total_eat)
	{
		if (time_diff(p->tm_1, timestamp()) >= (*ph.last_meal + p->tm_die))
		{
			printf("%d %d Is dead\n", (*ph.last_meal + p->tm_die), ph.num);
			*p->is_dead = 1;
			pthread_mutex_unlock(&p->print);
			return (0);
		}
		printf("%lld %d Is sleeping\n", time_diff(p->tm_1, timestamp()), ph.num);
	}
	else if (type == 't' && *p->is_dead == 0 && p->n_ph > *p->total_eat)
	{
		if (time_diff(p->tm_1, timestamp()) >= (*ph.last_meal + p->tm_die))
		{
			printf("%d %d Is dead\n", (*ph.last_meal + p->tm_die), ph.num);
			*p->is_dead = 1;
			pthread_mutex_unlock(&p->print);
			return (0);
		}
		printf("%lld %d Is thinking\n", time_diff(p->tm_1, timestamp()), ph.num);
	}
	pthread_mutex_unlock(&p->print);
	return (1);
}