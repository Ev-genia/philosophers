/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlarra <mlarra@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 16:01:40 by mlarra            #+#    #+#             */
/*   Updated: 2022/04/28 17:02:34 by mlarra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_print_think(t_one_philo *p)
{
	llint	time;

	pthread_mutex_lock(&p->set->mutex_print);
	time = ft_get_time_now();
	printf("%lld %d is thinking\n", time, p->name);
	pthread_mutex_unlock(&p->set->mutex_print);
}

void	ft_print_sleep(t_one_philo *p)
{
	llint	time;

	pthread_mutex_lock(&p->set->mutex_print);
	time = ft_get_time_now();
	printf("%lld %d is sleeping\n", time, p->name);
	pthread_mutex_unlock(&p->set->mutex_print);
}

void	ft_print_eat(t_one_philo *p)
{
	llint	time;

	pthread_mutex_lock(&p->set->mutex_print);
	time = ft_get_time_now();
	printf("%lld %d is eating\n", time, p->name);
	pthread_mutex_unlock(&p->set->mutex_print);
}

void	ft_print_forks(t_one_philo *p)
{
	llint	time;

	pthread_mutex_lock(&p->set->mutex_print);
	time = ft_get_time_now();
	printf("%lld %d has taken a fork\n", time, p->name);
	pthread_mutex_unlock(&p->set->mutex_print);
}

void	ft_print_die(t_one_philo *p)
{
	llint	time;

	pthread_mutex_lock(&p->set->mutex_print);
	time = ft_get_time_now();
	printf("%lld %d died\n", time, p->name);
	pthread_mutex_unlock(&p->set->mutex_print);
}
