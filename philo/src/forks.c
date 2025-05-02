/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcamerly <lcamerly@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 08:30:52 by lcamerly          #+#    #+#             */
/*   Updated: 2025/05/02 11:23:32 by lcamerly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

/**
 * @brief Fast fork acquisition strategy (unsafe).
 *
 * @details Philosophers always take the left fork first, then the right one.
 * This is simple and fast, but it can lead to a deadlock if all philosophers
 * grab their left fork at the same time, which doesn't happen because of the
 * delay created by the thread creation + the sleep in the main loop, but 
 * theoretically can still happen.
 * 
 * As this version is still mostly unsafe, it'll trigger the following warnings:
 * - lock-order-inversion (potential deadlock) with -fsanitize=thread
 * - lock order violated with valgrindvalgrind --tool=helgrind --fair-sched=try
 *
 * @param philo Pointer to the philosopher structure.
 *
 * @return None   
*/
void	fast_taking_forks(t_philo *philo)
{
	pthread_mutex_lock(&philo->fork_l->mutex);
	printfilo(TAKE_FIRST_FORK, philo);
	pthread_mutex_lock(&philo->fork_r->mutex);
	printfilo(TAKE_SECOND_FORK, philo);
}

/**
 * @brief Slow fork acquisition strategy (safe).
 *
 * Philosophers take the right fork first, then the left one.
 * This is a safe strategy that prevents deadlocks, but it is slower
 * than the fast version.
 *
 * @param philo Pointer to the philosopher structure.
 *
 * @return None
*/
void	slow_taking_forks(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(&philo->fork_l->mutex);
		printfilo(TAKE_FIRST_FORK, philo);
		pthread_mutex_lock(&philo->fork_r->mutex);
		printfilo(TAKE_SECOND_FORK, philo);
	}
	else
	{
		pthread_mutex_lock(&philo->fork_r->mutex);
		printfilo(TAKE_FIRST_FORK, philo);
		pthread_mutex_lock(&philo->fork_l->mutex);
		printfilo(TAKE_SECOND_FORK, philo);
	}
}
