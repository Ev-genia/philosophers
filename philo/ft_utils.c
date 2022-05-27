/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlarra <mlarra@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 17:33:56 by mlarra            #+#    #+#             */
/*   Updated: 2022/05/27 16:33:25 by mlarra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_usleep_fix(unsigned long time)
{
	unsigned long	t;

	t = ft_get_time_now();
	while (ft_get_time_now() - t < time)
		usleep(1);
}

unsigned long	ft_get_time_now(void)
{
	struct timeval	time;
	unsigned long	rez;

	gettimeofday(&time, NULL);
	rez = time.tv_sec * 1000 + time.tv_usec / 1000;
	return (rez);
}
