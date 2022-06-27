/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlarra <mlarra@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 11:04:29 by mlarra            #+#    #+#             */
/*   Updated: 2022/06/27 16:21:54 by mlarra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	ft_take_forks(t_one_philo *philo)
{
	int		current_index;
	int		passed_index;

	if (philo->set->n_phs == 1)
	{
		while (ft_validate_life(philo->set) == 1)
			usleep(1);
		return ;
	}
	current_index = philo->num;
	sem_wait(philo->set->sem_table[current_index]);
	sem_wait(philo->set->forks);
	ft_print_logs(philo, "has taken a fork");
	// if (philo->set->n_phs == 1)
	// {
	// 	while (ft_validate_life(philo->set) == 1)
	// 		usleep(1);
	// 	sem_post(philo->set->forks);
	// 	return ;
	// }
	sem_wait(philo->set->forks);
	ft_print_logs(philo, "has taken a fork");
	sem_wait(philo->sem_time);
	philo->time_start = ft_get_time_now();
	sem_post(philo->sem_time);
	ft_print_logs(philo, "is eating");
	// ft_usleep_fix(philo->set->t_eat);
	usleep(philo->set->t_eat * 1000);
	sem_wait(philo->sem_eat);
	philo->total_eat++;
	sem_post(philo->sem_eat);
	sem_post(philo->set->forks);
	sem_post(philo->set->forks);
	passed_index = (current_index + 1) % philo->set->n_phs;
	sem_post(philo->set->sem_table[passed_index]);
}

void	*ft_start_philo(t_one_philo *ph)
{
	pthread_t	ph_live;
	int			total_eat;

	pthread_create(&ph_live, NULL, ft_check_live, ph);
	pthread_detach(ph_live);
	sem_wait(ph->sem_time);
	ph->time_start = ft_get_time_now();
	sem_post(ph->sem_time);
	while (1)
	{
		if (ft_validate_life(ph->set) == 0)
				return (NULL);
		ft_take_forks(ph);
		if (ft_validate_life(ph->set) == 0)
				return (NULL);
		sem_wait(ph->sem_eat);
		total_eat = ph->total_eat;
		sem_post(ph->sem_eat);
		if (ph->set->must_eat != -1 && total_eat == ph->set->must_eat)
				return (NULL);
		ft_philo_sleep(ph);
		ft_print_logs(ph, "is thinking");
	}
	return (NULL);
}

void	ft_create_philo(t_one_philo *philo)
{
	int		i;
	// pid_t	name_pid;

	i = -1;
	while (++i < philo->set->n_phs)
	{
		// name_pid = fork();
		philo[i].pid_num = fork();
		if (philo[i].pid_num == 0)
		{
			ft_start_philo(&philo[i]);
// printf("\nexit %d philo\n", i);
			exit(0);
			return ;
		}
		// else
			// {
// printf("\nphilo[%d].pid_num = name_pid = %d\n", i, name_pid);
			// philo[i].pid_num = name_pid;
			// }
		usleep(1);
	}
}

void	*ft_wait(void *philos)
{
	t_one_philo*	phs;
	t_set	*sett;
	int		i;
	int		status;

	phs = philos;
	sett = phs->set;
	i = -1;
	// sem_wait(sett->sem_die);
	while (waitpid(-1, &status, 0) > 0)
	{
// printf("X\n");
		if (WEXITSTATUS(status))
		{
// printf("WEXITSTATUS(status): %d\n", WEXITSTATUS(status));
			while (++i < sett->n_phs)
				kill(phs[i].pid_num, SIGTERM);
		}
	}
// 	while (++i < sett->n_phs)
// 		{
// printf("\nft_wait %d philo\n", i);
// 			wait(&status);}
// printf("\nbefore sem_die ft_wait\n");
	sem_post(sett->sem_die);
// printf("\nafter sem_die ft_wait\n");
	return (NULL);
}

int	ft_all_eat(t_one_philo *ph)
{
	int	i;

	i = 0;
	while (i < ph->set->n_phs)
	{
		// sem_wait(ph[i].sem_eat);
// printf("\nph[%d].total_eat = %d\n", i, ph[i].total_eat);
		if (ph[i].total_eat < ph->set->must_eat)
		{
			// sem_post(ph[i].sem_eat);
			return (0);
		}
		// sem_post(ph[i].sem_eat);
		i++;
	}
// printf("\neats %d philo\n", i);
	return (1);
}

void	*ft_eats(void *phils)
{
	t_one_philo	*phs;

	phs = phils;
	while (1)
	{
		if (ft_all_eat(phs))
		{
			sem_wait(phs->set->living);
			phs->set->life = 0;
			sem_post(phs->set->sem_die);
			return (NULL);
		}
	}
	return (NULL);
}

int	main(int argc, char **argv)
{
	t_one_philo	*phils;
	pthread_t	lives;
	// pthread_t	eats;

	if (ft_check_arg(argc, argv) != 0)
	{
		ft_print(2, "Error argumens\n");
		return (1);
	}
	phils = ft_check_malloc(argv);
	if (phils == NULL)
	{
		ft_print(2, "Malloc error\n");
		return (1);
	}
	ft_init_set(phils, argv);
	ft_create_philo(phils);
// printf("end ft_cteate_philo\n");
	// pthread_create(&eats, NULL, ft_eats, phils);
	// pthread_detach(eats);
	pthread_create(&lives, NULL, ft_wait, phils);
	pthread_detach(lives);
// printf("end pthread_create ft_wait\n");
	ft_free_all(phils);
// printf("end ft_free_all\n");
	return (0);
}
