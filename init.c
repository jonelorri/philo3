/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jelorria <jelorria@student.42urduli>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 18:26:14 by jelorria          #+#    #+#             */
/*   Updated: 2022/11/11 18:26:16 by jelorria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_vals(t_p *p, char **argv, int argc)
{
	p->n_ph = ft_atoi(argv[1]);
	p->tm_die = ft_atoi(argv[2]);
	p->tm_eat = ft_atoi(argv[3]);
	p->tm_sleep = ft_atoi(argv[4]);
	if (argc == 6)
	{
		p->nbr_eat = ft_atoi(argv[5]);
		p->total_eat = malloc(sizeof(int));
		*p->total_eat = 0;
	}
	if (argc == 5)
	{
		p->nbr_eat = 100000;
		p->total_eat = malloc(sizeof(int));
		*p->total_eat = 0;
	}
	p->is_dead = malloc(sizeof(int));
	*p->is_dead = 0;
}

int	init_mutex(t_p *p)
{
	p->i = p->n_ph;
	while (--p->i >= 0)
	{
		if (pthread_mutex_init(&(p->forks[p->i]), NULL))
		{
			printf("Error\n");
			return (1);
		}
	}
	if (pthread_mutex_init(&(p->print), NULL))
	{
		printf("Error\n");
		return (1);
	}
	return (0);
}

int	check_vals(t_p *p)
{
	if (p->nbr_eat <= 0)
		return (1);
	if (p->n_ph < 1)
	{
		printf("There are no philosophers\n");
		return (1);
	}
	if (p->tm_die <= 0 || p->tm_eat <= 0 || p->tm_sleep <= 0)
	{
		printf("Error\n");
		return (1);
	}
	if (p->n_ph == 1)
	{
		printf("0 1 Has taken a Fork\n");
		usleep((p->tm_die) * 1000);
		printf("%d 1 Is dead\n", p->tm_die);
		return (1);
	}
	if (init_mutex(&*p))
		return (1);
	return (0);
}

int	ft_init(t_p *p, char **argv, int argc)
{
	init_vals(&*p, argv, argc);
	if (check_vals(&*p))
		return (1);
	p->i = p->n_ph;
	while (--p->i >= 0)
	{
		p->ph[p->i].id = p->i;
		p->ph[p->i].last_meal = malloc(sizeof(int));
		*p->ph[p->i].last_meal = 0;
		p->ph[p->i].nbr_meal = malloc(sizeof(int));
		*p->ph[p->i].nbr_meal = 0;
		p->ph[p->i].l_fork = p->i;
		p->ph[p->i].r_fork = (p->i + 1) % p->n_ph;
		p->ph[p->i].p = p;
	}
	return (0);
}
