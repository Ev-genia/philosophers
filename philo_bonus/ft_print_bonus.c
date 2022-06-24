/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlarra <mlarra@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 11:06:06 by mlarra            #+#    #+#             */
/*   Updated: 2022/06/15 17:44:32 by mlarra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	ft_print(int out, char *s)
{
	int	i;

	i = -1;
	while (s[++i])
		write(out, &s[i], 1);
}

int	ft_validate_life(t_set *sett)
{
	int	validate;

	// pthread_mutex_lock(&sett->mutex_life);
	sem_wait(sett->living);
	validate = sett->life;
	// pthread_mutex_unlock(&sett->mutex_life);
	sem_post(sett->living);
	return (validate);
}

void	ft_print_logs(t_one_philo *p, char *str)
{
	t_llint	time;

	if (ft_validate_life(p->set) == 0)
		return ;
	time = ft_get_time_now();
	// pthread_mutex_lock(&p->set->mutex_print);
	sem_wait(p->set->print);
	printf("%lld %d %s\n", time, p->name, str);
	// pthread_mutex_unlock(&p->set->mutex_print);
	sem_post(p->set->print);
}

void	ft_print_die(t_one_philo *p)
{
	t_llint	time;

	// pthread_mutex_lock(&p->set->mutex_print);
	sem_wait(p->set->print);
	time = ft_get_time_now();
	printf("%lld %d died\n", time, p->name);
	sem_post(p->set->print);
	// pthread_mutex_unlock(&p->set->mutex_print);
}
