/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   activities.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcamerly <lcamerly@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 10:15:57 by lcamerly          #+#    #+#             */
/*   Updated: 2025/04/29 19:43:38 by lcamerly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"
#include <stdio.h>

/**
 * @brief Print philosopher activity.
 *
 * @param status Status of the philosopher
 * @param philo Philosopher struct
 *
 * @details This function prints the activity of the philosopher.
 * The status is define as enum e_log in philosophers.h.
 *
 * @note The function locks the print mutex to ensure thread safety.
 * It also checks if the philosopher is dead before printing.
 *
 * @return None
*/
void	printfilo(int status, t_philo *philo)
{
	size_t	time;

	pthread_mutex_lock(philo->lock_print);
	time = gettime(MILLISECOND) - philo->start_time;
	if (!is_dead(philo))
	{
		if (status == TAKE_FIRST_FORK || status == TAKE_SECOND_FORK)
			printf("%-6ld"" %d has taken a fork\n", time, philo->id);
		else if (status == EATING)
			printf("%-6ld %d is eating\n", time, philo->id);
		else if (status == SLEEPING)
			printf("%-6ld"" %d is sleeping\n", time, philo->id);
		else if (status == THINKING)
			printf("%-6ld %d is thinking\n", time, philo->id);
		else if (status == DIED)
			printf("%-6ld %d died\n", time, philo->id);
	}
	pthread_mutex_unlock(philo->lock_print);
}

/**
 * @brief Eat function for the philosopher.
 *
 * @param philo Philosopher struct
 * 
 * @details This function locks the right and left forks, updates the 
 * last eat time, increments the eat count, and sleeps for the time to eat.
 * 
 * @note The current implementation produces a warning with 
 * -fsanitize=thread even though no deadlock occurs at all.
 * An alternative implementation that avoids the warning (but is slower)
 * would lock forks in different orders based on philosopher IDs.
 * This alternative would cause the program to fail tests like :
 * "./philo 3 1000 333 333" or "./philo 5 610 200 200".
 *
 * @code
 * if (philo->id % 2 == 0)
 * {
 *   pthread_mutex_lock(&philo->fork_l->mutex);
 *   printfilo(TAKE_FIRST_FORK, philo);
 *   pthread_mutex_lock(&philo->fork_r->mutex);
 *   printfilo(TAKE_SECOND_FORK, philo);
 * }
 * else
 * {
 *   pthread_mutex_lock(&philo->fork_r->mutex);
 *   printfilo(TAKE_FIRST_FORK, philo);
 *   pthread_mutex_lock(&philo->fork_l->mutex);
 *   printfilo(TAKE_SECOND_FORK, philo);
 * }
 * 
 * @return None
*/

void	eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->fork_r->mutex);
	printfilo(TAKE_FIRST_FORK, philo);
	pthread_mutex_lock(&philo->fork_l->mutex);
	printfilo(TAKE_SECOND_FORK, philo);
	printfilo(EATING, philo);
	pthread_mutex_lock(philo->lock_eat);
	philo->last_eat_time = gettime(MILLISECOND);
	philo->eat_count++;
	pthread_mutex_unlock(philo->lock_eat);
	ft_sleep(philo->time_to_eat);
	pthread_mutex_unlock(&philo->fork_l->mutex);
	pthread_mutex_unlock(&philo->fork_r->mutex);
}

/**
 * @brief Sleep function for the philosopher.
 *
 * @param philo Philosopher struct
 * 
 * @details This function prints the sleeping status of the 
 * philosopher and sleeps for the time to sleep.
 * 
 * @return None
*/
void	philo_sleep(t_philo *philo)
{
	printfilo(SLEEPING, philo);
	ft_sleep(philo->time_to_sleep);
}

/**
 * @brief Think function for the philosopher.
 *
 * @param philo Philosopher struct
 * 
 * @details This function prints the thinking status of the philosopher.
 * 
 * @return None
*/
void	think(t_philo *philo)
{
	printfilo(THINKING, philo);
}
