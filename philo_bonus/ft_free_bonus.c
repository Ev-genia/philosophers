/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlarra <mlarra@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 15:12:57 by mlarra            #+#    #+#             */
/*   Updated: 2022/06/25 01:37:19 by mlarra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	ft_free_all(t_one_philo *phil)
{
	int	i;

	i = -1;
// printf("\ntest 1\n");
	sem_wait(phil->set->sem_die);
// printf("\ntest 2\n");
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
	free(phil);
}