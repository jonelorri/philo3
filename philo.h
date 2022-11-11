/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jelorria <jelorria@student.42urduli>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 18:10:32 by jelorria          #+#    #+#             */
/*   Updated: 2022/11/11 18:10:33 by jelorria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdlib.h>
# include <stdio.h>
# include <pthread.h>
# include <unistd.h>
# include <sys/time.h>

typedef struct s_philo
{
	pthread_t		thread_id;
	int				id;
	int				num;
	int				l_fork;
	int				r_fork;
	int				*last_meal;
	int				*nbr_meal;
	struct s_p		*p;
}					t_philo;

typedef struct s_p
{
	int				n_ph;
	int				tm_die;
	int				tm_eat;
	int				tm_sleep;
	int				nbr_eat;
	int				*total_eat;
	int				*is_dead;
	int				i;
	long long		tm_1;
	t_philo			ph[200];
	pthread_mutex_t	forks[200];
	pthread_mutex_t	print;
}					t_p;

int			ft_init(t_p *p, char **argv, int argc);
int			ft_atoi(const char *str);
long long	timestamp(void);
long long	time_diff(long long past, long long pres);
int			execute(t_p *p);
char		*ft_itoa(int n);
int			print_message(void *arg, char type);
int			print_message(void *arg, char type);
void		smart_sleep(long long time, t_p *p, int nbr);

#endif
