/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   activities.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcamerly <lcamerly@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 10:15:57 by lcamerly          #+#    #+#             */
/*   Updated: 2025/04/28 10:47:15 by lcamerly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"
#include <stdbool.h>
#include <stdio.h>

void	printfilo(int status, t_philo *philo)
{
	size_t	time;

	pthread_mutex_lock(philo->lock_print);
	time = gettime(MILLISECOND) - philo->start_time;
	if (!is_dead(philo) || is_full(philo))
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

void eat(t_philo *philo)
{
    pthread_mutex_lock(philo->forklock_r->mutex);
    printfilo(TAKE_FIRST_FORK, philo);
    pthread_mutex_lock(philo->forklock_l->mutex);
    printfilo(TAKE_SECOND_FORK, philo);
    pthread_mutex_lock(philo->lock_eat);
    philo->last_eat_time = gettime(MICROSECOND);
    philo->is_eating = true;
    pthread_mutex_unlock(philo->lock_eat);
    printfilo(EATING, philo);
    ft_sleep(philo->start_time + philo->time_to_eat);
    pthread_mutex_unlock(philo->forklock_l->mutex);
    pthread_mutex_unlock(philo->forklock_r->mutex);
}