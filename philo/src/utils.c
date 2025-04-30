/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcamerly <lcamerly@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 10:35:47 by lcamerly          #+#    #+#             */
/*   Updated: 2025/04/30 09:40:56 by lcamerly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

bool is_dead(t_philo *philo)
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


void kill_mutexes(struct s_main *main)
{
    int i;

    i = -1;
    while (++i < main->nb_philo)
        pthread_mutex_destroy(&main->forks[i].mutex);
    pthread_mutex_destroy(&main->lock_eat);
    pthread_mutex_destroy(&main->lock_dead);
    pthread_mutex_destroy(&main->lock_print);
}

void* one_philo(void *philo_ptr)
{
    t_philo *philo;
    philo = (t_philo *)philo_ptr;
    
    pthread_mutex_lock(&philo->fork_l->mutex);
    printfilo(TAKE_FIRST_FORK, philo);
    ft_sleep(philo->time_to_die, philo);
    printfilo(DIED, philo);
    pthread_mutex_unlock(&philo->fork_l->mutex);
    return (NULL);
}

void set_dead(t_philo *philo)
{
    pthread_mutex_lock(philo->lock_dead);
    *philo->is_dead = true;
    pthread_mutex_unlock(philo->lock_dead);
}