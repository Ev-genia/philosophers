/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlarra <mlarra@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 12:59:25 by mlarra            #+#    #+#             */
/*   Updated: 2022/05/26 15:33:09 by mlarra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <stdlib.h>
# include <stdio.h>
# include <pthread.h>
# include <unistd.h>
# include <sys/time.h>

typedef long long int llint;
typedef pthread_mutex_t t_mutex;
typedef struct s_set//settings
{
	llint		n_phs;
	llint		t_die;
	llint		t_eat;
	llint		t_sleep;
	int			must_eat;
	int			life;
	t_mutex		*forks;
	t_mutex		mutex_print;
	t_mutex		mutex_life;
	t_mutex		mutex_t_start;
	pthread_t	thread_live;
}	t_set;

typedef struct s_one_philo//struct of one philosopher
{
	int			name;
	int			num;
	llint		time_start;
	int			l_fork_id;
	int			r_fork_id;
	int			total_eat;
	t_set		*set;//pointer to settings
	pthread_t	*thread_ph;
	// t_mutex		eat;
}	t_one_philo;

typedef struct s_philos
{
	t_mutex		general_mutex;
	t_one_philo	*phs;//[200];//array of pointer of philosophers
	t_set		*set;//pointer to settings
}	t_philos;

long long int  ft_atoi(const char *str);

void	ft_print_think(t_one_philo *p);
void	ft_print_sleep(t_one_philo *p);
void	ft_print_eat(t_one_philo *p);
void	ft_print_forks(t_one_philo *p);
void	ft_print_die(t_one_philo *p);
void	ft_print(int out, char *s);

void	ft_philo_think(t_one_philo *p);
void	ft_philo_sleep(t_one_philo *ph);
void	ft_usleep_fix(unsigned long time);

void	ft_take_forks(t_one_philo *philo);

unsigned long	ft_get_time_now(void);

void	ft_init_set(t_philos *philos, char **av);
void	ft_init_phs(t_one_philo *one_ph, int i, t_set *sett);

int	ft_check_arg(int ac, char **av);
t_philos	*ft_check_malloc(char **av);
void	*ft_check_live(void *philo);
int	ft_validate_life(t_set *sett);

void	ft_print(int out, char *s);
void	ft_print_logs(t_one_philo *p, char *str);
unsigned long	ft_get_time_now(void);

void	ft_free_all(t_philos *phls);

#endif
