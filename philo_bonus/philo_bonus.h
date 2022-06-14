/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlarra <mlarra@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 11:04:45 by mlarra            #+#    #+#             */
/*   Updated: 2022/06/08 13:06:58 by mlarra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H
# include <pthread.h>
# include <semaphore.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>

typedef long long int	t_llint;
typedef struct s_set
{
	t_llint		n_phs;
	t_llint		t_die;
	t_llint		t_eat;
	t_llint		t_sleep;
	int			must_eat;
	int			live;
	sem_t		*forks;
	sem_t		*print;
}	t_set;

typedef struct s_one_philo
{
	int			name;
	int			num;
	t_llint		time_start;
	int			total_eat;
	t_set		*set;
	pthread_t	thread_monitor;
}	t_one_philo;

// typedef struct s_philos
// {
// 	t_one_philo	*phs;
// 	t_set		*set;
// }	t_philos;

long long int	ft_atoi(const char *str);
int				ft_check_arg(int ac, char **av);
// ft_print.c
void	ft_print(int out, char *s);
//ft_init_bonus.c
void	ft_init_set(t_one_philo *philos, char **av);
//ft_utils_bonus.c
unsigned long	ft_get_time_now(void);

#endif