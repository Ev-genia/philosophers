/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlarra <mlarra@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 11:30:05 by mlarra            #+#    #+#             */
/*   Updated: 2022/03/21 18:01:04 by mlarra           ###   ########.fr       */
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

void	ft_init(char **param, t_philo *phil, int nbr)
{
	// if (param < 5 || param > 6)
	// 	return (1);
	phil->num = nbr;
	phil->set.time_to_die = ft_atoi(param[2]);
	phil->set.time_to_eat = ft_atoi(param[3]);
	phil->set.time_to_sleep = ft_atoi(param[4]);
	if (param[5])
		phil->set.each_must_eat = ft_atoi(param[5]);
}

void	*ft_phil_func(t_philo *p)
{
	 
}

int	main(int ac, char **av)
{
	pthread_t	*t_ph;
	int			i;
	t_philo		*ph; //array of philosophers

	if (ac < 5 || ac > 6 || av[2] < 0 || av[3] < 0 || av[4] < 0)
		return (1);
	// ? t_ph = malloc(sizeof(t_ph) * av[1])
	i = -1;
	while (++i < ft_atoi(av[1]))
	{
		ft_init(av, &ph[i], i);
		pthread_create(&t_ph[i], NULL, ft_phil_func, &ph[i]);
	}
	i = -1;
	while (++i < av[1])
		pthread_join(t_ph[i], NULL);
	i = -1;
	while (++i < av[1])
		pthread_detach(t_ph[i]);
	return (0);
}