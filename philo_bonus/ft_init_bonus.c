/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlarra <mlarra@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 12:06:39 by mlarra            #+#    #+#             */
/*   Updated: 2022/06/27 15:35:07 by mlarra           ###   ########.fr       */
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
	sem_unlink("sem_eat");
	sem_unlink("sem_time");
	one_ph->sem_eat = sem_open("sem_eat", O_CREAT, 0644, 1);
	one_ph->sem_time = sem_open("sem_time", O_CREAT, 0644, 1);
}



sem_t	*open_semaphore(char *name, int val)
{
	sem_t	*i;

	sem_unlink(name);
	i = sem_open(name, O_CREAT, 0644, val);
	return (i);
}

char	*make_semaphore_name(int num)
{
	char	*temp;
	char	*sem_name;

	temp = ft_itoa(num);
	sem_name = ft_strjoin("queue", temp);
	free(temp);
	return (sem_name);
}

void	ft_init_set(t_one_philo *philos, char **av)
{
	int	i;
	char	*sem_name;

	philos->set->n_phs = ft_atoi(av[1]);
	philos->set->t_die = ft_atoi(av[2]);
	philos->set->t_eat = ft_atoi(av[3]);
	philos->set->t_sleep = ft_atoi(av[4]);
	if (av[5])
		philos->set->must_eat = ft_atoi(av[5]);
	else
		philos->set->must_eat = -1;
	philos->set->life = 1;
	sem_unlink("sem_print");
	sem_unlink("sem_forks");
	sem_unlink("sem_living");
	sem_unlink("sem_died");
	philos->set->print = sem_open("sem_print", O_CREAT, 0644, 1);
	philos->set->forks = sem_open("sem_forks", O_CREAT, 0644, 
		philos->set->n_phs);
	philos->set->living = sem_open("sem_living", O_CREAT, 0644, 1);
	philos->set->sem_die = sem_open("sem_died", O_CREAT, 0644, 0);
	i = -1;
	while (++i < philos->set->n_phs)
	{
		sem_name = make_semaphore_name(i);
		philos->set->sem_table[i] = open_semaphore(sem_name, i % 2);
		free(sem_name);
		// if (philos->set->sem_table[i] < 0)
		// 	return (1);
		i++;
	}
	i = -1;
	while (++i < philos->set->n_phs)
		ft_init_phs(&philos[i], i, philos->set);
}
