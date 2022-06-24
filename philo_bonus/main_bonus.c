/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlarra <mlarra@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 11:04:29 by mlarra            #+#    #+#             */
/*   Updated: 2022/06/24 12:37:59 by mlarra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	ft_take_forks(t_one_philo *philo)
{
	// pthread_mutex_lock(&philo->set->global_mutex);
	// pthread_mutex_lock(&(philo->set->forks[philo->l_fork_id]));
	sem_wait(philo->set->forks);
	ft_print_logs(philo, "has taken a fork");
	if (philo->set->n_phs == 1)
	{
		while (ft_validate_life(philo->set) == 1)
			usleep(1);
		sem_post(philo->set->forks);
		// pthread_mutex_unlock(&philo->set->global_mutex);
		// pthread_mutex_unlock(&(philo->set->forks[philo->l_fork_id]));
		return ;
	}
	// pthread_mutex_lock(&(philo->set->forks[philo->r_fork_id]));
	sem_wait(philo->set->forks);
	ft_print_logs(philo, "has taken a fork");
	// pthread_mutex_unlock(&philo->set->global_mutex);
	// pthread_mutex_lock(&philo->set->mutex_t_start);
	philo->time_start = ft_get_time_now();
	// pthread_mutex_unlock(&philo->set->mutex_t_start);
	ft_print_logs(philo, "is eating");
	ft_usleep_fix(philo->set->t_eat);
	// pthread_mutex_lock(&philo->mutex_eat);
	sem_wait(philo->sem_eat);
	philo->total_eat++;
	// pthread_mutex_unlock(&philo->mutex_eat);
	sem_post(philo->sem_eat);
	// pthread_mutex_unlock(&(philo->set->forks[philo->l_fork_id]));
	// pthread_mutex_unlock(&(philo->set->forks[philo->r_fork_id]));
	sem_post(philo->set->forks);
	sem_post(philo->set->forks);
}

void	*ft_start_philo(t_one_philo *ph)
{
	pthread_t	ph_live;

	pthread_create(&ph_live, NULL, ft_check_live, ph);
	ph->time_start = ft_get_time_now();
	while (1)
	{
		if (ft_validate_life(ph->set) == 0)
			return (NULL);
// printf("1 ft_validate_life(ph->set) = %d\n", ft_validate_life(ph->set));
		ft_take_forks(ph);
		if (ft_validate_life(ph->set) == 0)
			return (NULL);
// printf("2 ft_validate_life(ph->set) = %d\n", ft_validate_life(ph->set));		
		ft_philo_sleep(ph);
		ft_print_logs(ph, "is thinking");
	}
	return (NULL);
}

void	ft_create_philo(t_one_philo *philo)
{
	int		i;
	pid_t	name_pid;

	i = -1;
	while (++i < philo->set->n_phs)
	{
		name_pid = fork();
		if (name_pid == 0)
		{
			ft_start_philo(&philo[i]);
printf("exit %d philo\n", i);
			exit(0);
			return ;
		}
		else
			philo[i].pid_num = name_pid;
		usleep(1);
	}
}

void	*ft_wait(void *settings)
{
	t_set	*sett;
	int		i;
	int		status;

	sett = settings;
	i = -1;
	sem_wait(sett->sem_die);
	while (++i < sett->n_phs)
		wait(&status);
	sem_post(sett->sem_die);
	return (NULL);
}

int	main(int argc, char **argv)
{
	t_one_philo	*phils;
	pthread_t	lives;

	if (ft_check_arg(argc, argv) != 0)
	{
		ft_print(2, "Error argumens\n");
		return (1);
	}
// printf("test1\n");
	// phils = malloc(sizeof(t_one_philo) * ft_atoi(argv[1]));
	// if (!phils)
	// {
	// 	ft_print(2, "Malloc error\n");
	// 	return (1);
	// }
	phils = ft_check_malloc(argv);
	if (phils == NULL)
	{
		ft_print(2, "Malloc error\n");
		return (1);
	}
// printf("test2\n");
	ft_init_set(phils, argv);
// printf("test3\n");
	ft_create_philo(phils);
	pthread_create(&lives, NULL, ft_wait, &phils->set);
	ft_free_all(phils);
}
