/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_think.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlarra <mlarra@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 16:04:02 by mlarra            #+#    #+#             */
/*   Updated: 2022/05/25 22:36:56 by mlarra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_philo_think(t_one_philo *p)
{
	if (p->set->life != 1)
		return ;
	ft_print_think(p);
// printf("TEST_think\n");
	// ft_take_forks(p);
}
