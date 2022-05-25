/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sleep.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlarra <mlarra@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 16:05:07 by mlarra            #+#    #+#             */
/*   Updated: 2022/05/25 23:55:15 by mlarra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_philo_sleep(t_one_philo *ph)
{
	ft_print_sleep(ph);
// printf("TEST1_sleep, t_sleep = %lld\n", ph->set->t_sleep);
	// usleep(ph->set->t_sleep * 1000);
	ft_usleep_fix(ph->set->t_sleep);
// printf("TEST_sleep\n");
	// ft_philo_think(ph);
}
