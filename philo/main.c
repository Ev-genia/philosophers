/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlarra <mlarra@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 11:30:05 by mlarra            #+#    #+#             */
/*   Updated: 2022/03/25 17:35:41 by mlarra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// enum {
//   N=5,                    // number of philosophers
//   THINKING=0,             // philosopher is thinking
//   HUNGRY=1,               // philosopher is trying to get forks
//   EATING=2,               // philosopher is eating
// };  

// #define LEFT (i+N-1)%N		// номер левого соседа 
// i #define RIGHT (i+1)%N      // номер правого соседа i

// int state[N];             // array to keep track of everyone's state
// std::mutex mutex_;        // mutual exclusion for critical regions
// std::binary_semaphore s[N]{0, 0, 0, 0, 0}; 
//                           // one semaphore per philosopher
// std::mutex mo;            // for synchronized cout

// void test(int i) {        // i: philosopher number, from 0 to N-1
//   if (state[i] == HUNGRY 
//    && state[LEFT] != EATING && state[RIGHT] != EATING) {
//     state[i] = EATING;
//     s[i].release();
//   }
// }

// void think(int i) {
//   int duration = myrand(400, 800);
//   {
//     std::lock_guard<std::mutex> gmo(mo);
//     std::cout<<i<<" thinks "<<duration<<"ms\n";
//   }
//   std::this_thread::sleep_for(std::chrono::milliseconds(duration));
// }

// void take_forks(int i) {  // i: philosopher number, from 0 to N-1
//   mutex_.lock();          // enter critical region
//   state[i] = HUNGRY;      // record fact that philosopher i is hungry
//   {
//     std::lock_guard<std::mutex> gmo(mo);
//     std::cout<<"\t\t"<<i<<" is hungry\n";
//   }
//   test(i);                // try to acquire 2 forks
//   mutex_.unlock();        // exit critical region
//   s[i].acquire();         // block if forks were not acquired
// } 

// void eat(int i) {
//   int duration = myrand(400, 800);
//   {
//     std::lock_guard<std::mutex> gmo(mo);
//     std::cout<<"\t\t\t\t"<<i<<" eats "<<duration<<"ms\n";
//   }
//   std::this_thread::sleep_for(std::chrono::milliseconds(duration));
// }

// void put_forks(int i) {   // i: philosopher number, from 0 to N-1
//   mutex_.lock();          // enter critical region
//   state[i] = THINKING;    // philosopher has finished eating
//   test(LEFT);             // see if left neighbor can now eat
//   test(RIGHT);            // see if right neighbor can now eat
//   mutex_.unlock();        // exit critical region
// }

// void philosopher(int i) { // i: philosopher number, from 0 to N-1
//   while (true) {          // repeat forever
//     think(i);             // philosopher is thinking
//     take_forks(i);        // acquire two forks or block
//     eat(i);               // yum-yum, spaghetti
//     put_forks(i);         // put both forks back on table
//   }
// }

// int main() {
//   std::cout<<"dp_14\n";

//   std::thread t0([&] {philosopher(0);});
//   std::thread t1([&] {philosopher(1);});
//   std::thread t2([&] {philosopher(2);});
//   std::thread t3([&] {philosopher(3);});
//   std::thread t4([&] {philosopher(4);});
//   t0.join();
//   t1.join();
//   t2.join();
//   t3.join();
//   t4.join();
// }

void	ft_init(char **param, t_philo *phil, int nbr, pthread_mutex_t *mutx, pthread_t thread)
{
	phil->num = nbr;
	phil->stream = thread;
// printf("phil->num: %d\n", phil->num);
	phil->set.n_philos = ft_atoi(param[1]);
	phil->set.t_die = ft_atoi(param[2]);
	phil->set.t_eat = ft_atoi(param[3]);
	phil->set.t_sleep = ft_atoi(param[4]);
	if (param[5])
		phil->set.each_must_eat = ft_atoi(param[5]);
	else
		phil->set.each_must_eat = -1;
	// init_forks
	//{

	phil->mut_print = malloc(sizeof(pthread_mutex_t *));
	pthread_mutex_init(phil->mut_print, NULL);
	phil->forks = mutx;
// printf("mutex %d\n", phil->num);
// printf("phil->forks[%d]: %p\n", phil->num, &(phil->forks[phil->num]));
	pthread_mutex_init(&(phil->forks[phil->num]), NULL);
// printf("mutex_init %d\n", phil->num);
	if (phil->num < (phil->num + phil->set.n_philos - 1) % phil->set.n_philos)
	{
		phil->fork_min_id = phil->num;
		phil->fork_max_id = (phil->num + phil->set.n_philos - 1) % phil->set.n_philos;
	}
	else
	{
		phil->fork_min_id = (phil->num + phil->set.n_philos - 1) % phil->set.n_philos;
		phil->fork_max_id = phil->num;
	}
	phil->numbers_of_eats = 0;
// printf("phil[%d]->fork_min_id: %d, phil[%d]->fork_max_id: %d\n", phil->num, phil->fork_min_id, phil->num, phil->fork_max_id);
	//}
	// phil->state = HUNGRY;
// printf("end ft_init %d\n", phil->num);
}

unsigned long	ft_get_time_now(void)
{
	struct timeval	time;
	unsigned long	rez;

	gettimeofday(&time, NULL);
	rez = time.tv_sec * 1000 + time.tv_usec / 1000;
	return (rez);
}

void	ft_eat(t_philo *man)
{
// printf("ft_eat %d\n", man->num);
// printf("man[%d]->fork_min_id: %d, man[%d]->fork_max_id: %d\n", man->num, man->fork_min_id, man->num, man->fork_max_id);
	pthread_mutex_lock(&(man->forks[man->fork_min_id]));
	pthread_mutex_lock(man->mut_print);
	printf("%lu %d has taken a fork\n", ft_get_time_now(), man->num);
	pthread_mutex_unlock(man->mut_print);
// printf("man->forks[%d]: %p\n", man->num, &(man->forks[man->num]));
	pthread_mutex_lock(&(man->forks[man->fork_max_id]));
	pthread_mutex_lock(man->mut_print);
	printf("%lu %d has taken a fork\n", ft_get_time_now(), man->num);
	pthread_mutex_unlock(man->mut_print);
	man->timer_begin = ft_get_time_now();
	pthread_mutex_lock(man->mut_print);
	printf("%lu %d is eating\n", ft_get_time_now(), man->num);
	pthread_mutex_unlock(man->mut_print);
	usleep(man->set.t_eat * 1000);
	man->numbers_of_eats++;
	pthread_mutex_unlock(&(man->forks[man->fork_min_id]));
	pthread_mutex_unlock(&(man->forks[man->fork_max_id]));
}

void	ft_sleep(t_philo *man)
{
	// pthread_mutex_lock(man->mut_print);
	printf("%lu %d is sleeping\n", ft_get_time_now(), man->num);
	// pthread_mutex_unlock(man->mut_print);
	usleep(man->set.t_sleep * 1000);
}

void	*ft_phil_func(void *phil)
{
	t_philo	*p;
	int		i;

	p = phil;
// printf("ft_phil_func %d\n", p->num);
	p->timer_begin = ft_get_time_now();
	i = 0;
	while (i < p->set.each_must_eat || p->set.each_must_eat == -1)
	{
		ft_eat(p);
		ft_sleep(p);
		// printf("%lu %d is sleeping\n", ft_get_time_now(), p->num);
		// usleep(p->set.time_to_sleep * 1000);
		// pthread_mutex_lock(p->mut_print);
		printf("%lu %d is thinking\n", ft_get_time_now(), p->num);
		// pthread_mutex_unlock(p->mut_print);
		i++;
	}
	return ((void *) 0);
}

// void	ft_control_life(t_philo *ph)
// {
// 	int	i;
// 	int	total;

// 	i = 0;
// 	total = ph[0].set.n_philos;
// 	while (i != total)
// 	{
// 		if ((ft_get_time_now() - ph[i].timer_begin) > ph[i].set.t_die)
// 		{
// 			printf("%lu %d died\n", ft_get_time_now(), ph[i].num);
// 			return ;
// 		}
		
// 		i++;
// 		if (i == total)
// 			i = 0;
// 	}
// }

void	*ft_control_life(void *phil)
{
	int	i;
	int	total;
	t_philo *ph;

	ph = phil;
	i = 0;
	total = ph[0].set.n_philos;
	while (i != total)
	{
		if ((ft_get_time_now() - ph[i].timer_begin) > ph[i].set.t_die)
		{
			pthread_mutex_lock(ph[i].mut_print);
			printf("%lu %d died\n", ft_get_time_now(), ph[i].num);
			pthread_mutex_unlock(ph[i].mut_print);

			i = -1;
			while (++i < ph->set.n_philos)
				pthread_detach(ph[i].stream);

			return ((void *) 0);
		}
		
		i++;
		if (i == total)
			i = 0;
	}
	return ((void *) 0);
}

void	ft_control_eat(t_philo *ph)
{
	int	i;
	int	total;
	int	eats;

	i = 0;
	
	total = ph[0].set.n_philos;
	while (1)//i != total)
	{
		i = 0;
		eats = 0;
		while (i < total)
		{
			if (ph[i].numbers_of_eats >= ph[i].set.each_must_eat)
				eats++;
			i++;
		}
		if (eats == total)
			return ;
		// i++;
		// if (i == total)
		// 	i = 0;
	}
}

int	ft_check_args(int argc, char **argv)
{
	int	i;

	if (argc < 5 || argc > 6)
		return (1);
	i = 2;
	while(argv[i])
	{
		if (ft_atoi(argv[i]) <= 0)
			return (1);
		i++;
	}
	return (0);
}

int	ft_check_malloc(pthread_t **stream, t_philo **philosophers, pthread_mutex_t **forks, char **arv)
{
	*stream = malloc(sizeof(pthread_t) * ft_atoi(arv[1]));
	if (!(*stream))
	{
printf("Error pthread malloc\n");
		return (1);
	}
	*philosophers = malloc(sizeof(t_philo) * ft_atoi(arv[1]));
	if (!(*philosophers))
	{
		free(*stream);
printf("Error philosophers malloc\n");
		return (1);
	}
	*forks = malloc(sizeof(pthread_mutex_t) *  ft_atoi(arv[1]));
	if (!(*forks))
	{
		free(*philosophers);
		free(*stream);
printf("Error mutex malloc\n");
		return (1);
	}
	return (0);
}

int	main(int ac, char **av)
{
	pthread_t	*t_ph;
	int			i;
	t_philo		*ph;// array of philosophers
	pthread_mutex_t	*mtx;// array of mutex
	pthread_t	*t_life;

	if (ft_check_args(ac, av) != 0)
	{
printf("Error arguments\n");
		return (1);
	}

	if (ft_check_malloc(&t_ph, &ph, &mtx, av) != 0)
		return (1);

	i = 0;
	while (i < ft_atoi(av[1]))
	{
		ft_init(av, &ph[i], i, mtx, t_ph[i]);
		i++;
	}

	i = 0;
	while (i < ft_atoi(av[1]))
	{
// printf("test %d\n", i);
		// ft_init(av, &ph[i], i, &mtx);
		if (i % 2 == 1)
			ft_sleep(&ph[i]);
		pthread_create(&t_ph[i], NULL, ft_phil_func, (void *) &ph[i]);

		// if (pthread_create(&t_ph[i], NULL, ft_phil_func, (void *) &ph[i]) == 0)
		// 	printf("-> yes, pthread_create\n");
		// else
		// 	printf("-> no, pthread_no_create\n");
			
// printf("test_sleep50\n");
		// usleep(50);
		i++;
	}
	
	// if (av[5])
	// {	ft_control_eat(ph);
	// 	printf("Each philosopher eats %d \n", ph[0].set.each_must_eat);
	// }
	// else
	// 	ft_control_life(ph);
	
	t_life = (pthread_t *) malloc(sizeof(pthread_t));
	pthread_create(t_life, NULL, ft_control_life, (void *) ph);
	// if (av[5])
	// 	ft_control_eat(ph);

	i = -1;
	while (++i < ft_atoi(av[1]))
	{
		pthread_mutex_destroy(&(ph[i].forks[ph->fork_max_id]));
		pthread_mutex_destroy(ph[i].mut_print);
	}

	i = -1;
	while (++i < ft_atoi(av[1]))
		pthread_detach(t_ph[i]);

	
	pthread_detach(*t_life);
	free(t_life);

	// ft_free(ph);
	free(ph->forks);
	free(ph);
	free(t_ph);
	return (0);
}