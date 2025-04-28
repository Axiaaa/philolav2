/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcamerly <lcamerly@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 10:35:47 by lcamerly          #+#    #+#             */
/*   Updated: 2025/04/28 10:48:03 by lcamerly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"
#include <unistd.h>

bool is_dead(t_philo *philo)
{
    pthread_mutex_lock(philo->lock_dead);
    if (philo->is_dead)
    {
        pthread_mutex_unlock(philo->lock_dead);
        return (true);
    }
    pthread_mutex_unlock(philo->lock_dead);
    return (false);
}

bool is_full(t_philo *philo)
{
    pthread_mutex_lock(philo->lock_eat);
    if (philo->eat_count >= philo->must_eat_count)
    {
        pthread_mutex_unlock(philo->lock_eat);
        return (true);
    }
    pthread_mutex_unlock(philo->lock_eat);
    return (false);
}

int ft_sleep(long time)
{
    long start_time;

    start_time = gettime(MICROSECOND);
    while (gettime(MICROSECOND) - start_time < time)
        usleep(100);
    return (0);
}

