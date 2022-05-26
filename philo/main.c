/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlarra <mlarra@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 12:59:31 by mlarra            #+#    #+#             */
/*   Updated: 2022/05/26 15:41:37 by mlarra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_usleep_fix(unsigned long time)
{
	unsigned long	t;

	t = ft_get_time_now();
	while (ft_get_time_now() - t < time)
		usleep(1);
}

void	ft_take_forks(t_one_philo *philo)
{
	pthread_mutex_lock(&(philo->set->forks[philo->l_fork_id]));
	ft_print_logs(philo, "has taken a fork");
	pthread_mutex_lock(&(philo->set->forks[philo->r_fork_id]));
	ft_print_logs(philo, "has taken a fork");
	pthread_mutex_lock(&philo->set->mutex_t_start);
	philo->time_start = ft_get_time_now();
	pthread_mutex_unlock(&philo->set->mutex_t_start);
	ft_print_logs(philo, "is eating");
	ft_usleep_fix(philo->set->t_eat);
	philo->total_eat++;
	pthread_mutex_unlock(&(philo->set->forks[philo->l_fork_id]));
	pthread_mutex_unlock(&(philo->set->forks[philo->r_fork_id]));
}

void	*ft_start_philo(void *p)
{
	t_one_philo	*ph;

	ph = p;
	ph->time_start = ft_get_time_now();
	while (1)
	{
		// pthread_mutex_lock(&ph->set->mutex_life);
		// if (ph->set->life != 1)
			// {pthread_mutex_unlock(&ph->set->mutex_life);
				// return (NULL);
				// }
		// pthread_mutex_unlock(&ph->set->mutex_life);
		if (ft_validate_life(ph->set) == 0)
			return (NULL);
		ft_take_forks(ph);
		if (ph->set->must_eat != -1 && ph->total_eat == ph->set->must_eat)
			return (NULL);
		ft_philo_sleep(ph);
		ft_philo_think(ph);
	}
	return (NULL);
}

void	ft_create_threads(t_philos *ps)
{
	int			i;
	int			rez;
	
	i = 0;
/*	while (i < ps->set->n_phs)
	{
		ps->phs[i].time_start = ft_get_time_now();
		rez = pthread_create(ps->phs[i].thread_ph, NULL, ft_start_philo, &ps->phs[i]);
		if (rez != 0)
			return (ft_print(2, "pthread_create_err"));
		i += 2;
		// ft_usleep_fix(5);
	}
	ft_usleep_fix(ps->set->t_eat);
	i = 1;
	while (i < ps->set->n_phs)
	{
		ps->phs[i].time_start = ft_get_time_now();
		rez = pthread_create(ps->phs[i].thread_ph, NULL, ft_start_philo, &ps->phs[i]);
		if (rez != 0)
			return (ft_print(2, "pthread_create_err"));
		i += 2;
		// ft_usleep_fix(5);
	}*/
	while (i < ps->set->n_phs)
	{
		// ps->phs[i].time_start = ft_get_time_now();
		rez = pthread_create(ps->phs[i].thread_ph, NULL, ft_start_philo, &ps->phs[i]);
		if (rez != 0)
			return (ft_print(2, "pthread_create_err"));
		i++;
		ft_usleep_fix(ps->set->t_eat);
	}
	pthread_create(&ps->set->thread_live, NULL, ft_check_live, ps);
}

void	ft_detach_threads(t_philos *p)
{
	int	i;

	i = -1;
	while (++i < p->set->n_phs)
		pthread_mutex_destroy(&p->set->forks[i]);
	pthread_mutex_destroy(&p->set->mutex_print);
	pthread_mutex_destroy(&p->general_mutex);
	i = -1;
	while (++i < p->set->n_phs)
		pthread_detach(*(p->phs[i].thread_ph));
	pthread_detach(p->set->thread_live);
}


int	main(int argc, char **argv)
{
	t_philos	*phils;
	int			i;

	if (ft_check_arg(argc, argv) != 0)
	{
		ft_print(2, "Error argumens\n");
		return(1);
	}
	phils = ft_check_malloc(argv);
	if (phils == NULL)
	{
		ft_print(2, "Malloc error\n");
		return (1);
	}
	ft_init_set(phils, argv);
	ft_create_threads(phils);
	// pthread_mutex_lock(&phils->general_mutex);
	// pthread_mutex_unlock(&phils->general_mutex);
	// ft_detach_threads(phils);
	i = 0;
	while (i < phils->set->n_phs)
	{
		pthread_join(*phils->phs[i].thread_ph, NULL);
		i++;
	}
	pthread_join(phils->set->thread_live, NULL);
	ft_free_all(phils);
	return (0);
}
