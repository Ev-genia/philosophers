/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlarra <mlarra@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/01 13:17:46 by mlarra            #+#    #+#             */
/*   Updated: 2022/05/26 16:16:14 by mlarra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_free_all(t_philos *phls)
{
	// int	i;

	// i = -1;
	// while (++i < phls->set->n_phs)
	// 	free(&phls->phs[i].thread_ph);
	free(phls->set->forks);
	free(phls->set);
	free(phls->phs);
	free(phls);
}

// void	ft_free(int i, phls->phs)
// {}
