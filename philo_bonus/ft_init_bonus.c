/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlarra <mlarra@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 12:06:39 by mlarra            #+#    #+#             */
/*   Updated: 2022/06/14 15:31:08 by mlarra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	ft_init_phs(t_one_philo *one_ph, int i, t_set *sett)
{
	one_ph->num = i;
	one_ph->name = one_ph->num + 1;
	one_ph->time_start = ft_get_time_now();
	one_ph->set = sett;
	one_ph->total_eat = 0;
}

void	ft_init_set(t_one_philo *philos, char **av)
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
	philos->set->live = 1;
	sem_unlink("print");
	sem_unlink("forks");
	philos->set->print = sem_open("sem_print", O_CREAT, 0644, 1);
	philos->set->forks = sem_open("sem_forks", O_CREAT, 0644, 
		philos->set->n_phs);
	i = -1;
	while (++i < philos->set->n_phs)
		ft_init_phs(&philos[i], i, philos->set);
}
