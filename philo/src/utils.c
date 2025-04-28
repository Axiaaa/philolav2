/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcamerly <lcamerly@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 10:35:47 by lcamerly          #+#    #+#             */
/*   Updated: 2025/04/28 18:01:01 by lcamerly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

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


void kill_mutexes(struct s_main *main)
{
    int i;

    i = -1;
    while (++i < main->nb_philo)
        pthread_mutex_destroy(main->forks[i].mutex);
    pthread_mutex_destroy(&main->lock_eat);
    pthread_mutex_destroy(&main->lock_dead);
    pthread_mutex_destroy(&main->lock_print);
}