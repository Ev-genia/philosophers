/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlarra <mlarra@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 11:30:05 by mlarra            #+#    #+#             */
/*   Updated: 2022/03/24 17:42:27 by mlarra           ###   ########.fr       */
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

void	ft_init(char **param, t_philo *phil, int nbr, pthread_mutex_t **mutx, pthread_mutex_t *mo)
{

	phil->num = nbr;

printf("phil->num: %d\n", phil->num);
	phil->set.n_philos = ft_atoi(param[1]);
	phil->set.time_to_die = ft_atoi(param[2]);
	phil->set.time_to_eat = ft_atoi(param[3]);
	phil->set.time_to_sleep = ft_atoi(param[4]);
	if (param[5])
		phil->set.each_must_eat = ft_atoi(param[5]);
	else
		phil->set.each_must_eat = -1;
	// init_forks
	//{
	// phil->fork_max->take_fork = malloc(sizeof(pthread_mutex_t *));

	phil->forks = mutx;
printf("mutex %d\n", phil->num);
printf("phil->forks[%d]: %p\n", phil->num, phil->forks[phil->num]);
	pthread_mutex_init(phil->forks[phil->num], NULL);
printf("mutex_init %d\n", phil->num);
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
printf("phil[%d]->fork_min_id: %d, phil[%d]->fork_max_id: %d\n", phil->num, phil->fork_min_id, phil->num, phil->fork_max_id);
	//}
	// phil->state = HUNGRY;
printf("end ft_init %d\n", phil->num);
pthread_mutex_unlock(mo);
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
printf("ft_eat %d\n", man->num);
printf("man[%d]->fork_min_id: %d, man[%d]->fork_max_id: %d\n", man->num, man->fork_min_id, man->num, man->fork_max_id);
	pthread_mutex_lock(man->forks[man->fork_min_id]);
	printf("%lu %d has taken a fork\n", ft_get_time_now(), man->num);
printf("man->forks[%d]: %p\n", man->num, man->forks[man->num]);
	pthread_mutex_lock(man->forks[man->fork_max_id]);
	printf("%lu %d has taken a fork\n", ft_get_time_now(), man->num);
	man->start_time = ft_get_time_now();
	printf("%lu %d is eating\n", ft_get_time_now(), man->num);
	usleep(man->set.time_to_eat * 1000);
	pthread_mutex_unlock(man->forks[man->fork_min_id]);
	pthread_mutex_unlock(man->forks[man->fork_max_id]);
}

void	ft_sleep(t_philo *man)
{
	printf("%lu %d is sleeping\n", ft_get_time_now(), man->num);
	usleep(man->set.time_to_sleep * 1000);
}

void	*ft_phil_func(void *phil)
{
	t_philo	*p;
	int		i;

	p = phil;
printf("ft_phil_func %d\n", p->num);
	p->start_time = ft_get_time_now();
	i = 0;
	while (i < p->set.each_must_eat || p->set.each_must_eat == -1)
	{
		ft_eat(p);
		ft_sleep(p);
		// printf("%lu %d is sleeping\n", ft_get_time_now(), p->num);
		// usleep(p->set.time_to_sleep * 1000);
		printf("%lu %d is thinking\n", ft_get_time_now(), p->num);
		i++;
	}
	return ((void *) 0);
}

void	ft_control_life(t_philo *ph)
{
	int	i;
	int	total;

	i = 0;
	total = ph[0].set.n_philos;
	while (i != total)
	{
		if ((ft_get_time_now() - ph[i].start_time) > ph[i].set.time_to_die)
		{
			printf("%lu %d died\n", ft_get_time_now(), ph[i].num);
			return ;
		}
		i++;
		if (i == total)
			i = 0;
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
pthread_mutex_t	*table;

	// if (ac < 5 || ac > 6 || ft_atoi(av[2]) <= 0 || ft_atoi(av[3]) <= 0 || ft_atoi(av[4]) <= 0)
	if (ft_check_args(ac, av) != 0)
	{
printf("Error arguments\n");
		return (1);
	}

	
// 	t_ph = malloc(sizeof(pthread_t) * ft_atoi(av[1]));
// 	if (!t_ph)
// 	{
// printf("Error pthread malloc\n");
// 		return (1);
// 	}
// 	ph = malloc(sizeof(t_philo) * ft_atoi(av[1]));
// 	if (!ph)
// 	{
// 		free(t_ph);
// printf("Error philosophers malloc\n");
// 		return (1);
// 	}
// 	mtx = malloc(sizeof(pthread_mutex_t) *  ft_atoi(av[1]));
// 	if (!mtx)
// 	{
// 		free(ph);
// 		free(t_ph);
// printf("Error mutex malloc\n");
// 		return (1);
// 	}
	if (ft_check_malloc(&t_ph, &ph, &mtx, av) != 0)
		return (1);

pthread_mutex_init(table, NULL);

	i = 0;
	while (i < ft_atoi(av[1]))
	{
pthread_mutex_lock(table);
printf("test %d\n", i);
		ft_init(av, &ph[i], i, &mtx, table);
		if (i % 2 == 1)
			ft_sleep(&ph[i]);
		// pthread_create(&t_ph[i], NULL, ft_phil_func, (void *) &ph[i]);

		if (pthread_create(&t_ph[i], NULL, ft_phil_func, (void *) &ph[i]) == 0)
			printf("-> yes, pthread_create\n");
		else
			printf("-> no, pthread_no_create\n");
			
printf("test_sleep50\n");
		// usleep(50);
		i++;
	}

	ft_control_life(ph);

	i = -1;
	while (++i < ft_atoi(av[1]))
		pthread_mutex_destroy(ph[i].forks[ph->fork_max_id]);

	i = -1;
	while (++i < ft_atoi(av[1]))
		pthread_detach(t_ph[i]);

	// ft_free(ph);
	free(*(ph->forks));
	free(ph);
	free(t_ph);
	return (0);
}