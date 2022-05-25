/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlarra <mlarra@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 17:29:12 by mlarra            #+#    #+#             */
/*   Updated: 2022/05/24 16:37:04 by mlarra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_init_phs(t_one_philo *one_ph, int i, t_set *sett)
{
	one_ph->num = i;
	one_ph->name = one_ph->num + 1;
	one_ph->time_start = ft_get_time_now();
	one_ph->set = sett;
	if (one_ph->num < (one_ph->num + one_ph->set->n_phs - 1) % one_ph->set->n_phs)
	{
		one_ph->l_fork_id = one_ph->num;
		one_ph->r_fork_id = (one_ph->num + one_ph->set->n_phs - 1) % one_ph->set->n_phs;
	}
	else
	{
		one_ph->l_fork_id = (one_ph->num + one_ph->set->n_phs - 1) % one_ph->set->n_phs;
		one_ph->r_fork_id = one_ph->num;
	}
	one_ph->total_eat = 0;
	pthread_mutex_init(&one_ph->set->forks[one_ph->num], NULL);
	pthread_mutex_init(&one_ph->set->mutex_print, NULL);
	pthread_mutex_init(&one_ph->eat, NULL);
	pthread_mutex_lock(&one_ph->eat);
}

void	ft_init_set(t_philos *philos, char **av)
{
	int	i;

	philos->set->n_phs = ft_atoi(av[1]);
	philos->set->t_die = ft_atoi(av[2]);
	philos->set->t_eat = ft_atoi(av[3]);
	philos->set->t_sleep = ft_atoi(av[4]);
	if (av[5])
		philos->set->must_eat = ft_atoi(av[5]);
	else
		philos->set->must_eat = -1;
	pthread_mutex_init(&philos->general_mutex, NULL);
	pthread_mutex_lock(&philos->general_mutex);
	philos->set->life = 1;
	i = -1;
	while (++i < philos->set->n_phs)
		ft_init_phs(&philos->phs[i], i, philos->set);
}
