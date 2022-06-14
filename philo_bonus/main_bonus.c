/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlarra <mlarra@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 11:04:29 by mlarra            #+#    #+#             */
/*   Updated: 2022/06/14 15:28:32 by mlarra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	ft_start_philo(t_one_philo *ph)
{
	ph->time_start = ft_get_time_now();
	while (1)
	{
		// if (ft_validate_life(ph->set) == 0)
		// 	return (NULL);
		ft_take_forks(ph);
		// if (ft_validate_life(ph->set) == 0)
		// 	return (NULL);
		ft_philo_sleep(ph);
		ft_print_logs(ph, "is thinking");
	}
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
			ft_start_philo(philo);
			// exit(0);
			return ;
		}

	}
}

int	main(int argc, char **argv)
{
	t_one_philo	*phils;

	if (ft_check_arg(argc, argv) != 0)
	{
		ft_print(2, "Error argumens\n");
		return (1);
	}
	phils = malloc(sizeof(t_one_philo) * ft_atoi(argv[1]));
	if (!phils)
	{
		ft_print(2, "Malloc error\n");
		return (1);
	}
	ft_init_set(phils, argv);
	ft_create_philo(phils);

}
