/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlarra <mlarra@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 17:30:34 by mlarra            #+#    #+#             */
/*   Updated: 2022/05/24 16:42:50 by mlarra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_check_arg(int ac, char **av)
{
	int	i;
	int	j;

	if (ac < 5 || ac > 6)
		return (1);
	if (ft_atoi(av[1]) < 2)
		return (1);
	i = 0;
	while (av[++i])
	{
		if (ft_atoi(av[i]) <= 0)
			return (1);
// printf("av[%d]: %s\n", i, av[i]);
		j = -1;
		while(av[i][++j])
		{
// printf("av[%d][%d]: %c\n", i, j, av[i][j]);
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
		return (NULL);
	phls->set->forks = malloc(sizeof(pthread_mutex_t) * ft_atoi(av[1]));
	if (!phls->set->forks)
		return (NULL);
	i = -1;
	while (++i < ft_atoi(av[1]))
	{
		phls->phs[i].thread_ph = malloc(sizeof(pthread_t) * ft_atoi(av[1]));
		if (!phls->phs[i].thread_ph)
		{
			// ft_free(); //освободить предыдущие
			return (NULL);
		}
	}
	return (phls);
}

// void	*ft_check_must_eat(void *ph)
// {
// 	t_philos	*phl;
// 	// t_one_philo	*arr_ph;
// 	// t_set		*settings;
// 	int			fact_eat;
// 	int			i;

// 	phl = ph;
// 	// arr_ph = ;
// 	// settings = phl->set;
// 	fact_eat = -1;
// 	while (++fact_eat < phl->set->must_eat)
// 	{
// 		i = -1;
// 		while (++i < phl->set->n_phs)
// 			pthread_mutex_lock(&phl->phs[i].eat);
// 	}
// 	pthread_mutex_unlock(&phl->general_mutex);
// 	return (NULL);	
// }

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

	time = ft_get_time_now();
// printf("time - p.time_start: %lld, ", time - p.time_start);
// printf("p.set->t_die: %lld\n", p.set->t_die);
	if (time - p->time_start >= p->set->t_die && ft_is_must_eat(p))
		return (1);
	return (0);
}

int	ft_all_end(t_philos *ph)
{
	int	i;

	i = 0;
	while (i < ph->phs->num)
	{
		if (ph->phs[i].total_eat < ph->set->must_eat)
			return (0);
		i++;
	}
	return (1);
}

void	*ft_check_live(void *philo)
{
	t_philos	*ph;
	// t_one_philo	*arr_ph;
	int			i;
	llint	time;

	ph = philo;
	time = ft_get_time_now();
	// arr_ph = arr;
	i = 0;
	// while (i < ph->phs[i].set->n_phs)
	while (1)
	{
		i = 0;
		while (i < ph->phs[i].set->n_phs)
		{
			// if (time - ph->phs[i].time_start - 1 >= ph->phs[i].set->t_die)
			if (ft_check_die(&ph->phs[i]))
			{
				ph->set->life = 0;
				ft_print_die(&ph->phs[i]);
				pthread_mutex_unlock(&ph->general_mutex);
				return (NULL);
			}
			if (ft_all_end(ph))
				return (NULL);
			i++;
		}
	}
	return (NULL);
}
