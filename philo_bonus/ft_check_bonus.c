/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlarra <mlarra@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 10:59:03 by mlarra            #+#    #+#             */
/*   Updated: 2022/06/24 16:30:01 by mlarra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	ft_check_arg(int ac, char **av)
{
	int	i;
	int	j;

	if (ac < 5 || ac > 6)
		return (1);
	i = 0;
	while (av[++i])
	{
		if (ft_atoi(av[i]) <= 0)
			return (1);
		j = -1;
		while (av[i][++j])
		{
			if ((av[i][j] < '0' || av[i][j] > '9') && av[i][j] != '+')
				return (1);
		}
	}
	return (0);
}

t_one_philo	*ft_check_malloc(char **av)
{
	t_one_philo	*phls;
	
	phls = malloc(sizeof(t_one_philo) * ft_atoi(av[1]));
	if (!phls)
	{
		ft_print(2, "Malloc error\n");
		return (NULL);
	}
	phls->set = malloc(sizeof(t_set));
	if (!phls->set)
	{
		free(phls);
		return (NULL);
	}
	return (phls);
}

int	ft_check_die(t_one_philo *p)
{
	t_llint	time;

	sem_wait(p->sem_time);
	time = ft_get_time_now();
	if (time - p->time_start > p->set->t_die)
	{
		sem_post(p->sem_time);
		return (1);
	}
	sem_post(p->sem_time);
	return (0);
}

// int	ft_all_eat(t_one_philo *ph)
// {
// 	int	i;

// 	i = 0;
// 	while (i < ph->set->n_phs)
// 	{
// 		sem_wait(ph->sem_eat);
// 		if (ph[i].total_eat < ph->set->must_eat)
// 		{
// 			sem_post(ph->sem_eat);
// 			return (0);
// 		}
// 		sem_post(ph->sem_eat);
// 		i++;
// 	}
// 	return (1);
// }

// void	*ft_check_live(void *philos)
// {
// 	t_one_philo	*ph;

// 	ph = philos;
// 	while (1)
// 	{
// 		if (ft_check_die(ph))
// 			// || (ph->set->must_eat != -1 && ft_all_eat(ph)))
// 		{
// 			sem_wait(ph->set->living);
// 			ph->set->life = 0;
// 			sem_post(ph->set->sem_die);
// 			// if (ft_check_die(ph))
// 				ft_print_die(ph);
// 			return (NULL);
// 		}
// 	}
// 	return (NULL);
// }

void	*ft_check_live(void *philos)
{
	t_one_philo	*ph;

	ph = philos;
	while (1)
	{
		if (ft_get_time_now() - ph->time_start > (unsigned long long)ph->set->t_die)
		{
			sem_wait(ph->set->living);
			ph->set->life = 0;
			sem_post(ph->set->sem_die);
			ft_print_die(ph);
			return (NULL);
		}
	}
	return (NULL);
}
