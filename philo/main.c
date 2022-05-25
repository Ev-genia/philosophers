/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlarra <mlarra@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 12:59:31 by mlarra            #+#    #+#             */
/*   Updated: 2022/05/24 18:23:38 by mlarra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_take_forks(t_one_philo *philo)
{
	pthread_mutex_lock(&(philo->set->forks[philo->l_fork_id]));
	ft_print_forks(philo);
	pthread_mutex_lock(&(philo->set->forks[philo->r_fork_id]));
	ft_print_forks(philo);
	philo->time_start = ft_get_time_now();
// printf("test1\n");
	ft_print_eat(philo);
// printf("test2\n");
// printf("ft_get_time_now():%lu - philo->time_start: %lld\n", ft_get_time_now(), philo->time_start);
// printf("philo->set->t_eat: %lld\n", philo->set->t_eat);
// printf("philo->set->t_eat: %lld\n", philo->set->t_eat * 1000);
// printf("philo->total_eat before eating: %d\n", philo->total_eat);
	usleep(philo->set->t_eat * 1000);
// printf("test3\n");
	philo->total_eat++;
// printf("philo->total_eat: %d\n", philo->total_eat);
	pthread_mutex_unlock(&philo->eat);
	pthread_mutex_unlock(&(philo->set->forks[philo->l_fork_id]));
	pthread_mutex_unlock(&(philo->set->forks[philo->r_fork_id]));
	ft_philo_sleep(philo);
}

void	*ft_start_philo(void *p)
{
	t_one_philo	*ph;

	ph = p;
	ft_take_forks(ph);
	return (NULL);
}

void	ft_create_threads(t_philos *ps)
{
	int			i;
	int			rez;
	// pthread_t	th_must_eat;
	
	// if (ps->set->must_eat)
	// 	pthread_create(&th_must_eat, NULL, ft_check_must_eat, ps);
	i = 0;
	while (i < ps->set->n_phs)
	{
// printf("ps->set->n_phs: %lld\n", ps->set->n_phs);
// printf("ps->phs[%d]\n", i);
		ps->phs[i].time_start = ft_get_time_now();
		rez = pthread_create(ps->phs[i].thread_ph, NULL, ft_start_philo, &ps->phs[i]);
		if (rez != 0)
			return (ft_print(2, "pthread_create_err"));
		// usleep(5);
		i += 2;
	}
	i = 1;
	while (i < ps->set->n_phs)
	{
// printf("ps->phs[%d]\n", i);
// printf("ps->set->n_phs: %lld\n", ps->set->n_phs);		
		ps->phs[i].time_start = ft_get_time_now();
		rez = pthread_create(ps->phs[i].thread_ph, NULL, ft_start_philo, &ps->phs[i]);
		if (rez != 0)
			return (ft_print(2, "pthread_create_err"));
		// usleep(5);
		i += 2;
	}
	pthread_create(&ps->set->thread_live, NULL, ft_check_live, ps);
// printf("thread_live create\n");
}

void	ft_detach_threads(t_philos *p)
{
	int	i;

// i = -1;
// while (++i < p->set->n_phs)
// 	pthread_join(*(p->phs[i].thread_ph), NULL);
// pthread_join(p->set->thread_live, NULL);

	i = -1;
	while (++i < p->set->n_phs)
	{
		pthread_mutex_destroy(&p->phs[i].eat);
		pthread_mutex_destroy(&p->set->forks[i]);
	}
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

	if (ft_check_arg(argc, argv) != 0)
	{
		ft_print(2, "Error argumens\n");
		return(1);
	}
// printf("ft_check_arg(argc, argv) = %d\n", ft_check_arg(argc, argv));
	phils = ft_check_malloc(argv);
	if (phils == NULL)
	{
		ft_print(2, "Malloc error\n");
		return (1);
	}
	ft_init_set(phils, argv);
	ft_create_threads(phils);
// printf("2-1\n");
	pthread_mutex_lock(&phils->general_mutex);
// printf("2-2\n");
	pthread_mutex_unlock(&phils->general_mutex);
	ft_detach_threads(phils);
	ft_free_all(phils);
	return (0);
}
