/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlarra <mlarra@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 17:33:56 by mlarra            #+#    #+#             */
/*   Updated: 2022/05/26 15:38:43 by mlarra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_print(int out, char *s)
{
	int	i;

	i = -1;
	while (s[++i])
		write(out, &s[i], 1);
}

unsigned long	ft_get_time_now(void)
{
	struct timeval	time;
	unsigned long	rez;

	gettimeofday(&time, NULL);
	rez = time.tv_sec * 1000 + time.tv_usec / 1000;
	return (rez);
}

int	ft_validate_life(t_set *sett)
{
	int	validate;
	pthread_mutex_lock(&sett->mutex_life);
	validate = sett->life;
	pthread_mutex_unlock(&sett->mutex_life);
	return (validate);
}

void	ft_print_logs(t_one_philo *p, char *str)
{
	llint	time;
	
	if (ft_validate_life(p->set) == 0)
		return ;
	time = ft_get_time_now();
	pthread_mutex_lock(&p->set->mutex_print);
	printf("%lld %d %s\n", time, p->name, str);
	pthread_mutex_unlock(&p->set->mutex_print);
}
