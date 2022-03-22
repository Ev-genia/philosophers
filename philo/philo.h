/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlarra <mlarra@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 11:30:09 by mlarra            #+#    #+#             */
/*   Updated: 2022/03/22 12:32:59 by mlarra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef PHILO_H
# define PHILO_H
# include <pthread.h>
# include <stdio.h>
# include <sys/time.h>

enum e_state
{
	THINKING,
	HUNGRY,
	EATING,
	SLEEPING
};

typedef struct s_philo
{
	int				num;
	struct timeval	start_time;
	int				numbers_of_eats;
	int				state; // состояния философа
	t_forks			forks;
	t_settings		set;
}	t_philo;

typedef struct s_forks
{
	int				id;
	pthread_mutex_t	*take_fork;
}	t_forks;

typedef struct s_settings
{
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	each_must_eat;
}	t_settings;

int	ft_atoi(const char *str);

#endif