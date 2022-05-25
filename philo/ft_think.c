/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_think.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlarra <mlarra@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 16:04:02 by mlarra            #+#    #+#             */
/*   Updated: 2022/05/13 17:21:32 by mlarra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_philo_think(t_one_philo *p)
{
// printf("1 ft_philo_think  p->set->life: %d\n", p->set->life);
	if (p->set->life != 1)
		return ;
// printf("2 ft_philo_think\n");	
	ft_print_think(p);
	ft_take_forks(p);
}
