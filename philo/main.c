/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlarra <mlarra@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 11:30:05 by mlarra            #+#    #+#             */
/*   Updated: 2022/03/29 16:18:02 by mlarra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_write(int out, char *s)//2, "Error arguments\n")
{
	int	i;

	i = 0;
	while (s[i])
	{
		write(out, &s[i], 1);
		i++;
	}
	write(out, "\n", 1);
}

void	ft_init(char **param, t_philo *phil, int nbr, pthread_mutex_t *mutx, pthread_t thread)
{
	phil->num = nbr;
	phil->name = phil->num + 1;
	phil->stream = thread;
	phil->set.n_philos = ft_atoi(param[1]);
	phil->set.t_die = ft_atoi(param[2]);
	phil->set.t_eat = ft_atoi(param[3]);
	phil->set.t_sleep = ft_atoi(param[4]);
	if (param[5])
		phil->set.each_must_eat = ft_atoi(param[5]);
	else
		phil->set.each_must_eat = -1;
	phil->mut_print = malloc(sizeof(pthread_mutex_t *));
	phil->forks = mutx;
	pthread_mutex_init(&(phil->forks[phil->num]), NULL);
	if (phil->num < (phil->num + phil->set.n_philos - 1) % phil->set.n_philos)
	{
		phil->fork_min_id = phil->num;
		phil->fork_max_id = (phil->num + phil->set.n_philos - 1) % phil->set.n_philos;
	}
	else
	{
		phil->fork_min_id = (phil->num + phil->set.n_philos - 1) % phil->set.n_philos;
		phil->fork_max_id = phil->num;
	}
	phil->numbers_of_eats = 0;
}

unsigned long	ft_get_time_now(void)
{
	struct timeval	time;
	unsigned long	rez;

	gettimeofday(&time, NULL);
	rez = time.tv_sec * 1000 + time.tv_usec / 1000;
	return (rez);
}

void	ft_eat(t_philo *man)
{
	pthread_mutex_lock(&(man->forks[man->fork_min_id]));
	printf("%lu %d has taken a fork\n", ft_get_time_now(), man->name);
	pthread_mutex_lock(&(man->forks[man->fork_max_id]));
	printf("%lu %d has taken a fork\n", ft_get_time_now(), man->name);
	man->timer_begin = ft_get_time_now();
	printf("%lu %d is eating\n", ft_get_time_now(), man->name);
	usleep(man->set.t_eat * 1000);
	man->numbers_of_eats++;
	pthread_mutex_unlock(&(man->forks[man->fork_min_id]));
	pthread_mutex_unlock(&(man->forks[man->fork_max_id]));
}

void	ft_sleep(t_philo *man)
{
	printf("%lu %d is sleeping\n", ft_get_time_now(), man->name);
	usleep(man->set.t_sleep * 1000);
}

void	ft_think(t_philo *man)
{
	printf("%lu %d is thinking\n", ft_get_time_now(), man->name);
}

void	*ft_phil_func(void *phil)
{
	t_philo	*p;
	int		i;

	p = phil;

	p->timer_begin = ft_get_time_now();
	i = 0;
	while (i < p->set.each_must_eat || p->set.each_must_eat == -1)
	{
		ft_eat(p);
		ft_sleep(p);
		ft_think(p);
		i++;
	}
	return ((void *) 0);
}

// void	ft_control_life(t_philo *ph)
// {
// 	int	i;
// 	int	total;

// 	i = 0;
// 	total = ph[0].set.n_philos;
// 	while (i != total)
// 	{
// 		if ((ft_get_time_now() - ph[i].timer_begin) > ph[i].set.t_die)
// 		{
// 			printf("%lu %d died\n", ft_get_time_now(), ph[i].num);
// 			return ;
// 		}
		
// 		i++;
// 		if (i == total)
// 			i = 0;
// 	}
// }

void	*ft_control_life(void *phil)
{
	int	i;
	int	total;
	t_philo *ph;

	ph = phil;
	i = 0;
	total = ph[0].set.n_philos;
	while (1)//i != total)
	{
		if ((ft_get_time_now() - ph[i].timer_begin) > ph[i].set.t_die)
		{
			printf("%lu %d died\n", ft_get_time_now(), ph[i].name);
			return ((void *) 0);
		}
		
		// i++;
		// if (i == total)
		// 	i = 0;
	}
	return ((void *) 0);
}

void	ft_control_eat(t_philo *ph)
{
	int	i;
	int	total;
	int	eats;

	i = 0;
	
	total = ph[0].set.n_philos;
	while (1)
	{
		i = 0;
		eats = 0;
		while (i < total)
		{
			if (ph[i].numbers_of_eats >= ph[i].set.each_must_eat)
				eats++;
			i++;
		}
		if (eats == total)
			return ;
	}
}

int	ft_check_args(int argc, char **argv)
{
	int	i;

	if (argc < 5 || argc > 6)
		return (1);
	i = 1;
	while(i < argc)
	{
		if (ft_atoi(argv[i]) <= 0)
		{
			return (1);
		}
		i++;
	}
	return (0);
}

int	ft_check_malloc(pthread_t **stream, t_philo **philosophers, pthread_mutex_t **forks, char **arv)
{
	*stream = malloc(sizeof(pthread_t) * ft_atoi(arv[1]));
	if (!(*stream))
	{
ft_write(2, "Error pthread malloc");
		return (1);
	}
	*philosophers = malloc(sizeof(t_philo) * ft_atoi(arv[1]));
	if (!(*philosophers))
	{
		free(*stream);
ft_write(2, "Error philosophers malloc");
		return (1);
	}
	*forks = malloc(sizeof(pthread_mutex_t) *  ft_atoi(arv[1]));
	if (!(*forks))
	{
		free(*philosophers);
		free(*stream);
ft_write(2, "Error mutex malloc");
		return (1);
	}
	return (0);
}

int	main(int ac, char **av)
{
	pthread_t	*t_ph;
	int			i;
	t_philo		*ph;// array of philosophers
	pthread_mutex_t	*mtx;// array of mutex

	if (ft_check_args(ac, av) != 0)
	{
		ft_write(2, "Error arguments");
		return (1);
	}

	if (ft_check_malloc(&t_ph, &ph, &mtx, av) != 0)
		return (1);

	i = 0;
	while (i < ft_atoi(av[1]))
	{
		ft_init(av, &ph[i], i, mtx, t_ph[i]);
		i++;
	}
	i = 0;
	while (i < ft_atoi(av[1]))
	{
		if (i % 2 == 1)
			ft_think(&ph[i]);
		pthread_create(&t_ph[i], NULL, ft_phil_func, (void *) &ph[i]);
		i++;
	}
	ft_control_life(ph);
	i = 0;
	while (i < ft_atoi(av[1]))
	{
		pthread_mutex_destroy(&(ph[i].forks[ph->fork_max_id]));
		i++;
	}
	i = -1;
	while (++i < ft_atoi(av[1]))
		pthread_detach(t_ph[i]);
	free(ph->forks);
	free(ph);
	free(t_ph);
	return (0);
}