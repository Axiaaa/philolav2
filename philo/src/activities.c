/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   activities.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcamerly <lcamerly@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 10:15:57 by lcamerly          #+#    #+#             */
/*   Updated: 2025/05/02 11:40:54 by lcamerly         ###   ########.fr       */
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
	time = gettime(MILLISECOND, philo) - philo->start_time;
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
 * @note More details about the fork acquisition strategy can be found in
 * the forks.c file.
 *
 * @return None
*/
void	eat(t_philo *philo)
{
	if (FAST)
		fast_taking_forks(philo);
	else
		slow_taking_forks(philo);
	printfilo(EATING, philo);
	pthread_mutex_lock(philo->lock_eat);
	philo->last_eat_time = gettime(MILLISECOND, philo);
	philo->eat_count++;
	pthread_mutex_unlock(philo->lock_eat);
	ft_sleep(philo->time_to_eat, philo);
	pthread_mutex_unlock(&philo->fork_r->mutex);
	pthread_mutex_unlock(&philo->fork_l->mutex);
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
	ft_sleep(philo->time_to_sleep, philo);
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
