/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlarra <mlarra@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 11:30:09 by mlarra            #+#    #+#             */
/*   Updated: 2022/03/21 17:58:44 by mlarra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef PHILO_H
# define PHILO_H
# include <pthread.h>
# include <stdio.h>

enum e_state
{
	THINKING,
	HUNGRY,
	EATING,
	SLEEPING
};

typedef struct s_philo
{
	int			num;
	time_t		run_time;
	int			numbers_of_eats;
	int			*state; //массив состояний философа
	t_forks		forks;
	t_settings	set;
}	t_philo;

typedef struct s_forks
{
	int				id;
	pthread_mutex_t	take_mutex;
}	t_forks;

typedef struct s_settings
{
	time_t	time_to_die;
	time_t	time_to_eat;
	time_t	time_to_sleep;
	int		each_must_eat;
}	t_settings;

int	ft_atoi(const char *str);

#endif