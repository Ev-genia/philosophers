/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sleep.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlarra <mlarra@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 16:05:07 by mlarra            #+#    #+#             */
/*   Updated: 2022/04/28 16:05:20 by mlarra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_philo_sleep(t_one_philo *ph)
{
	ft_print_sleep(ph);
	usleep(ph->set->t_sleep);
	ft_philo_think(ph);
}
