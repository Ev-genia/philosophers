/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlarra <mlarra@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 17:30:34 by mlarra            #+#    #+#             */
/*   Updated: 2022/05/27 12:47:14 by mlarra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_check_arg(int ac, char **av)
{
	int	i;
	int	j;

	if (ac < 5 || ac > 6)
		return (1);
	// if (ft_atoi(av[1]) < 2)
	// 	return (1);
	i = 0;
	while (av[++i])
	{
		if (ft_atoi(av[i]) <= 0)
			return (1);
		j = -1;
		while(av[i][++j])
		{
			if ((av[i][j] < '0' || av[i][j] > '9'))// || (av[i][j] == '-' && av[i][j] == '+'))
				return (1);
		}
	}
	return (0);
}

t_philos	*ft_check_malloc(char **av)
{
	int i;
	t_philos	*phls;
	
	phls = malloc(sizeof(t_philos));
	if (!phls)
		return (NULL);
	phls->set = malloc(sizeof(t_set));
	if (!phls->set)
	{
		free(phls);
		return (NULL);
	}
	phls->set->forks = malloc(sizeof(pthread_mutex_t) * ft_atoi(av[1]));
	if (!phls->set->forks)
	{
		free(phls);
		free(phls->set);
		return (NULL);
	}
	phls->phs = malloc(sizeof(t_one_philo) * ft_atoi(av[1]));
	if (!phls->phs)
	{
		free(phls);
		free(phls->set);
		free(phls->set->forks);
		return (NULL);
	}
	i = -1;
	while (++i < ft_atoi(av[1]))
	{
		phls->phs[i].thread_ph = malloc(sizeof(pthread_t));
		if (!phls->phs[i].thread_ph)
		{
			// ft_free(); //освободить предыдущие
			// ft_free(i, phls);
			free(phls->phs);
			free(phls->set->forks);
			free(phls->set);
			free(phls);
			return (NULL);
		}
	}
	return (phls);
}

int	ft_is_must_eat(t_one_philo *p)
{
	if (p->set->must_eat == -1)
		return (1);
	if (p->total_eat < p->set->must_eat)
		return (1);
	return (0);
}

int	ft_check_die(t_one_philo *p)
{
	llint	time;

	pthread_mutex_lock(&p->set->mutex_t_start);
	time = ft_get_time_now();
	if (time - p->time_start > p->set->t_die)
	{
		pthread_mutex_unlock(&p->set->mutex_t_start);
		return (1);
	}
	pthread_mutex_unlock(&p->set->mutex_t_start);
	return (0);
}

int	ft_all_eat(t_philos *ph)
{
	int	i;

	i = 0;
	while (i < ph->set->n_phs)
	{
		if (ph->phs[i].total_eat < ph->set->must_eat)
			return (0);
		i++;
	}
	return (1);
}

void	*ft_check_live(void *philos)
{
	t_philos	*ph;
	int			i;
	llint		time;

	ph = philos;
	time = ft_get_time_now();
	while (1)
	{
		i = 0;
		while (i < ph->set->n_phs)
		{
			if (ft_check_die(&ph->phs[i]))
			{
				pthread_mutex_lock(&ph->set->mutex_life);
				ph->set->life = 0;
				pthread_mutex_unlock(&ph->set->mutex_life);
				ft_print_die(&ph->phs[i]);
				// pthread_mutex_unlock(&ph->general_mutex);
				return (NULL);
			}
			if (ph->set->must_eat != -1 && ft_all_eat(ph))
			{
				// pthread_mutex_unlock(&ph->general_mutex);
				return (NULL);
			}
			i++;
		}
	}
	return (NULL);
}
