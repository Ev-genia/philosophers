/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlarra <mlarra@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 17:30:34 by mlarra            #+#    #+#             */
/*   Updated: 2022/04/28 17:32:49 by mlarra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_check_arg(int ac, char **av)
{
	int	i;
	int	j;

	if (ac < 5 || ac > 6)
		return (1);
	i = 0;
	while (av[++i])
	{
		j = -1;
		while(av[i][++j])
		{
			if ((av[i][j] < '0' || av[i][j] > '9') && (av[i][j] == '-' || av[i][j] == '+'))
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
	if (! phls->set)
		return (NULL);
	phls->set->forks = malloc(sizeof(pthread_mutex_t) * ft_atoi(av[1]));
	if (!phls->set->forks)
		return (NULL);
	i = -1;
	while (++i < ft_atoi(av[1]))
	{
		phls->phs[i] = malloc(sizeof(t_one_philo));
		phls->phs[i]->thread_ph = malloc(sizeof(pthread_t) * ft_atoi(av[1]));
		if (!phls->phs[i] || !phls->phs[i]->thread_ph)
		{
			// ft_free(); //освободить предыдущие
			return (NULL);
		}
	}
	return (phls);
}

void	*ft_check_must_eat(void *ph)
{
	t_philos	*phl;
	// t_one_philo	*arr_ph;
	// t_set		*settings;
	int			fact_eat;
	int			i;

	phl = ph;
	// arr_ph = ;
	// settings = phl->set;
	fact_eat = -1;
	while (++fact_eat < phl->set->must_eat)
	{
		i = -1;
		while (++i < phl->set->n_phs)
			pthread_mutex_lock(&phl->phs[i]->eat);
	}
	pthread_mutex_unlock(&phl->general_mutex);
	return (NULL);	
}

void	*ft_check_live(void *philo)
{
	t_philos	*ph;
	// t_one_philo	*arr_ph;
	int			i;
	// llint	time;

	ph = philo;
	// time = ft_get_time_now();
	// arr_ph = arr;
	i = 0;
	while (i < ph->phs[i]->set->n_phs)
	{
		if ((llint)time - ph->phs[i]->time_start > ph->phs[i]->set->t_die)
		{
			ft_print_die(ph->phs[i]);
			pthread_mutex_unlock(&ph->general_mutex);
		}
		i++;
	}
	return (NULL);
}
