/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlarra <mlarra@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 12:59:31 by mlarra            #+#    #+#             */
/*   Updated: 2022/04/28 17:35:22 by mlarra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// int	ft_check_arg(int ac, char **av)
// {
// 	int	i;
// 	int	j;

// 	if (ac < 5 || ac > 6)
// 		return (1);
// 	i = 0;
// 	while (av[++i])
// 	{
// 		j = -1;
// 		while(av[i][++j])
// 		{
// 			if ((av[i][j] < '0' || av[i][j] > '9') && (av[i][j] == '-' || av[i][j] == '+'))
// 				return (1);
// 		}
// 	}
// 	return (0);
// }

// void	ft_print(int out, char *s)
// {
// 	int	i;

// 	i = -1;
// 	while (s[++i])
// 		write(out, &s[i], 1);
// }

// t_philos	*ft_check_malloc(char **av)
// {
// 	int i;
// 	t_philos	*phls;
	
// 	phls = malloc(sizeof(t_philos));
// 	if (!phls)
// 		return (NULL);
// 	phls->set = malloc(sizeof(t_set));
// 	if (! phls->set)
// 		return (NULL);
// 	phls->set->forks = malloc(sizeof(pthread_mutex_t) * ft_atoi(av[1]));
// 	if (!phls->set->forks)
// 		return (NULL);
// 	i = -1;
// 	while (++i < ft_atoi(av[1]))
// 	{
// 		phls->phs[i] = malloc(sizeof(t_one_philo));
// 		phls->phs[i]->thread_ph = malloc(sizeof(pthread_t) * ft_atoi(av[1]));
// 		if (!phls->phs[i] || !phls->phs[i]->thread_ph)
// 		{
// 			// ft_free(); //освободить предыдущие
// 			return (NULL);
// 		}
// 	}
// 	return (phls);
// }

// unsigned long	ft_get_time_now(void)
// {
// 	struct timeval	time;
// 	unsigned long	rez;

// 	gettimeofday(&time, NULL);
// 	rez = time.tv_sec * 1000 + time.tv_usec / 1000;
// 	return (rez);
// }

// void	ft_init_phs(t_one_philo *one_ph, int i, t_set *sett)
// {
// 	one_ph->num = i;
// 	one_ph->name = one_ph->num + 1;
// 	one_ph->time_start = ft_get_time_now();
// 	one_ph->set = sett;
// 	if (one_ph->num < (one_ph->num + one_ph->set->n_phs - 1) % one_ph->set->n_phs)
// 	{
// 		one_ph->l_fork_id = one_ph->num;
// 		one_ph->r_fork_id = (one_ph->num + one_ph->set->n_phs - 1) % one_ph->set->n_phs;
// 	}
// 	else
// 	{
// 		one_ph->l_fork_id = (one_ph->num + one_ph->set->n_phs - 1) % one_ph->set->n_phs;
// 		one_ph->r_fork_id = one_ph->num;
// 	}
// 	one_ph->total_eat = 0;
// 	pthread_mutex_init(&(one_ph->set->forks[one_ph->num]), NULL);
// 	pthread_mutex_init(&(one_ph->set->mutex_print), NULL);
// 	pthread_mutex_init(&(one_ph->eat), NULL);
// }

// void	ft_init_set(t_philos *philos, char **av)
// {
// 	int	i;

// 	philos->set->n_phs = ft_atoi(av[1]);
// 	philos->set->t_die = ft_atoi(av[2]);
// 	philos->set->t_eat = ft_atoi(av[3]);
// 	philos->set->t_sleep = ft_atoi(av[4]);
// 	if (av[5])
// 		philos->set->must_eat = ft_atoi(av[5]);
// 	pthread_mutex_init(&philos->general_mutex, NULL);
// 	pthread_mutex_lock(&philos->general_mutex);
// 	i = -1;
// 	while (++i < philos->set->n_phs)
// 		ft_init_phs(philos->phs[i], i, philos->set);
// }

// void	ft_print_forks(t_one_philo *p)
// {
// 	llint	time;

// 	pthread_mutex_lock(&p->set->mutex_print);
// 	time = ft_get_time_now();
// 	printf("%lld %d has taken a fork\n", time - p->time_start, p->name);
// 	pthread_mutex_unlock(&p->set->mutex_print);
// }

// void	ft_print_eat(t_one_philo *p)
// {
// 	llint	time;

// 	pthread_mutex_lock(&p->set->mutex_print);
// 	time = ft_get_time_now();
// 	printf("%lld %d is eating\n", time - p->time_start, p->name);
// 	pthread_mutex_unlock(&p->set->mutex_print);
// }

// void	ft_print_sleep(t_one_philo *p)
// {
// 	llint	time;

// 	pthread_mutex_lock(&p->set->mutex_print);
// 	time = ft_get_time_now();
// 	printf("%lld %d is sleeping\n", time - p->time_start, p->name);
// 	pthread_mutex_unlock(&p->set->mutex_print);
// }

// void	ft_print_think(t_one_philo *p)
// {
// 	llint	time;

// 	pthread_mutex_lock(&p->set->mutex_print);
// 	time = ft_get_time_now();
// 	printf("%lld %d is thinking\n", time - p->time_start, p->name);
// 	pthread_mutex_unlock(&p->set->mutex_print);
// }

// void	ft_philo_think(t_one_philo *p)
// {
// 	ft_print_think(p);
// 	ft_take_forks(p);
// }

// void	ft_philo_sleep(t_one_philo *ph)
// {
// 	ft_print_sleep(ph);
// 	usleep(ph->set->t_sleep);
// 	ft_philo_think(ph);
// }

void	ft_take_forks(t_one_philo *philo)
{
	pthread_mutex_lock(&(philo->set->forks[philo->l_fork_id]));
	ft_print_forks(philo);
	pthread_mutex_lock(&(philo->set->forks[philo->num]));
	ft_print_forks(philo);
	philo->time_start = ft_get_time_now();
	ft_print_eat(philo);
	usleep(philo->set->t_eat);
	pthread_mutex_unlock(&(philo->set->forks[philo->l_fork_id]));
	pthread_mutex_unlock(&(philo->set->forks[philo->num]));
	philo->total_eat++;
	ft_philo_sleep(philo);
}

void	*ft_start_philo(void *p)
{
	t_one_philo	*ph;

printf("5\n");
	ph = p;
printf("ft_start_philo: ph->num = %d\n", ph->num);
	ph->time_start = ft_get_time_now();
	ft_take_forks(ph);
	return (NULL);
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
// 			pthread_mutex_lock(&phl->phs[i]->eat);
// 	}
// 	pthread_mutex_unlock(&phl->general_mutex);
// 	return (NULL);	
// }

// void	*ft_check_live(void *philo)
// {
// 	t_philos	*ph;
// 	// t_one_philo	*arr_ph;
// 	int			i;
// 	// llint	time;

// 	ph = philo;
// 	// time = ft_get_time_now();
// 	// arr_ph = arr;
// 	i = 0;
// 	while (i < ph->phs[i]->set->n_phs)
// 	{
// 		if ((llint)time - ph->phs[i]->time_start > ph->phs[i]->set->t_die)
// 		{
// 			ft_print_die(ph->phs[i]);
// 			pthread_mutex_unlock(&ph->general_mutex);
// 		}
// 		i++;
// 	}
// 	return (NULL);
// }

void	ft_create_threads(t_philos *ps)
{
	int			i;
	int			rez;
	pthread_t	th_must_eat;
	
printf("3\n");
	if (ps->set->must_eat)
		pthread_create(&th_must_eat, NULL, ft_check_must_eat, ps);
printf("4\n");
	i = -1;
	while (++i < ps->set->n_phs)
	{
printf("ft_create_threads: ps->phs[i]->num = %d\n", ps->phs[i]->num);
		rez = pthread_create(ps->phs[i]->thread_ph, NULL, ft_start_philo, &ps->phs[i]);
		if (rez != 0)
			return (ft_print(2, "pthread_create_err"));
	}
	pthread_create(&ps->set->thread_live, NULL, ft_check_live, ps);
}

void	ft_detach_threads(t_philos *p)
{
	int	i;

	i = -1;
	while (++i < p->set->n_phs)
	{
		pthread_mutex_destroy(&p->phs[i]->eat);
		pthread_mutex_destroy(&p->set->forks[i]);
	}
	pthread_mutex_destroy(&p->set->mutex_print);
	pthread_mutex_destroy(&p->general_mutex);
	i = -1;
	while (++i < p->set->n_phs)
		pthread_detach(*(p->phs[i]->thread_ph));
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
	phils = ft_check_malloc(argv);
	if (phils == NULL)
	{
		ft_print(2, "Malloc error\n");
		return (1);
	}
	ft_init_set(phils, argv);
printf("1\n");
	ft_create_threads(phils);
printf("2\n");
	pthread_mutex_lock(&phils->general_mutex);
	pthread_mutex_unlock(&phils->general_mutex);
	ft_detach_threads(phils);
printf("The end\n");
	return (0);
}
