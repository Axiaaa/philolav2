/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcamerly <lcamerly@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 10:35:47 by lcamerly          #+#    #+#             */
/*   Updated: 2025/05/02 11:42:08 by lcamerly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

/**
 * @brief Check if the philosopher is dead.
 *
 * @param philo Pointer to the philosopher structure.
 *
 * @return true if the philosopher is dead, false otherwise.
*/
bool	is_dead(t_philo *philo)
{
	pthread_mutex_lock(philo->lock_dead);
	if (*philo->is_dead)
	{
		pthread_mutex_unlock(philo->lock_dead);
		return (true);
	}
	pthread_mutex_unlock(philo->lock_dead);
	return (false);
}

/**
 * @brief Check if all philosophers are full.
 *
 * @param main Pointer to the main structure.
 * @param finished_eating Number of philosophers that have finished eating.
 *
 * @return true if all philosophers are full, false otherwise.
*/
void	kill_mutexes(struct s_main *main)
{
	int	i;

	i = -1;
	while (++i < main->nb_philo)
		pthread_mutex_destroy(&main->forks[i].mutex);
	pthread_mutex_destroy(&main->lock_eat);
	pthread_mutex_destroy(&main->lock_dead);
	pthread_mutex_destroy(&main->lock_print);
}

/**
* @brief Function executed when there is only one philosopher.
*
* @param philo_ptr Pointer to the philosopher structure.
*
* @details This function locks the left fork, sleeps for the time to die,
* and then prints that the philosopher has died.
* It is used when there is only one philosopher in the simulation.
*
* @return NULL
*/
void	*one_philo(void *philo_ptr)
{
	t_philo	*philo;

	philo = (t_philo *)philo_ptr;
	pthread_mutex_lock(&philo->fork_l->mutex);
	printfilo(TAKE_FIRST_FORK, philo);
	ft_sleep(philo->time_to_die, philo);
	printfilo(DIED, philo);
	pthread_mutex_unlock(&philo->fork_l->mutex);
	return (NULL);
}

/**
 * @brief Set the philosopher as dead.
 *
 * @param philo Pointer to the philosopher structure.
 *
 * @return None
*/
void	set_dead(t_philo *philo)
{
	pthread_mutex_lock(philo->lock_dead);
	*philo->is_dead = true;
	pthread_mutex_unlock(philo->lock_dead);
}
