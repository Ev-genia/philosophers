/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlarra <mlarra@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 11:30:09 by mlarra            #+#    #+#             */
/*   Updated: 2022/03/28 17:37:02 by mlarra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef PHILO_H
# define PHILO_H
# include <pthread.h>
# include <stdio.h>
# include <sys/time.h>
# include <unistd.h>
# include <stdlib.h>

// enum e_state
// {
// 	THINKING,
// 	HUNGRY,
// 	EATING,
// 	SLEEPING
// };

// typedef struct s_forks
// {
// 	int				id;
// 	pthread_mutex_t	*take_fork;
// }	t_forks;

typedef struct s_settings
{
	int				n_philos;
	unsigned long	t_die;
	unsigned long	t_eat;
	unsigned long	t_sleep;
	int				each_must_eat;
}	t_settings;

typedef struct s_philo
{
	int				num;
	int				name;
	pthread_t		stream;
	unsigned long	timer_begin;
	int				numbers_of_eats;
	// int				state; // состояния философа
	int				fork_min_id;
	int				fork_max_id;
	pthread_mutex_t	*forks;
	pthread_mutex_t	*mut_print;
	t_settings		set;
}	t_philo;

long long int	ft_atoi(const char *str);

#endif