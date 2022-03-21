/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlarra <mlarra@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 11:30:09 by mlarra            #+#    #+#             */
/*   Updated: 2022/03/21 13:40:50 by mlarra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// enum {
//   N=5,                    // number of philosophers
//   THINKING=0,             // philosopher is thinking
//   HUNGRY=1,               // philosopher is trying to get forks
//   EATING=2,               // philosopher is eating
// };  

// #define LEFT (i+N-1)%N		// номер левого соседа 
// i #define RIGHT (i+1)%N      // номер правого соседа i

#ifndef PHILO_H
# define PHILO_H
# include <pthread.h>
# include <stdio.h>

typedef struct s_philo
{
	int			num;
	t_settings	set;
	t_forks		*forks;
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
}	t_settings;


#endif