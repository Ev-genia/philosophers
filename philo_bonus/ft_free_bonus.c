/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlarra <mlarra@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 15:12:57 by mlarra            #+#    #+#             */
/*   Updated: 2022/06/27 15:54:47 by mlarra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	ft_free_all(t_one_philo *phil)
{
	int	i;
	char	*sem_name;

	i = -1;
// printf("before sem_die ft_free\n");
	sem_wait(phil->set->sem_die);
// printf("afret sem_die ft_free\n");
	while (++i < phil->set->n_phs)
		kill(phil[i].pid_num, SIGTERM);
	sem_unlink("sem_print");
	sem_unlink("sem_forks");
	sem_unlink("sem_living");
	sem_unlink("sem_died");
	sem_close(phil->set->print);
	sem_close(phil->set->forks);
	sem_close(phil->set->living);
	sem_close(phil->set->sem_die);
	i = -1;
	while (++i < phil->set->n_phs)
	{
		sem_close(phil->set->sem_table[i]);
		sem_name = make_semaphore_name(i);
		sem_unlink(sem_name);
		free(sem_name);
	}
	free(phil->set->sem_table);
	free(phil->set);
	free(phil);
}