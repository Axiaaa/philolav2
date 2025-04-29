/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcamerly <lcamerly@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 16:58:30 by lcamerly          #+#    #+#             */
/*   Updated: 2025/04/29 18:01:14 by lcamerly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"
#include <pthread.h>
#include <stdio.h>


void *main_loop(void *philo_ptr)
{
    t_philo *philo;

    philo = (t_philo *)philo_ptr;
    if (philo->id % 2 == 0)
        ft_sleep(1);
    while (!is_dead(philo))
    {
        eat(philo);
        philo_sleep(philo);
        think(philo);
    }
    return (NULL);
}


bool thread_join(struct s_main *main, pthread_t monitor_thread)
{
    int i;

    i = 0;
    while (i < main->nb_philo)
    {
        if (pthread_join(main->philos[i].thread, NULL) != 0)
            return (false);
        i++;
    }
    if (pthread_join(monitor_thread, NULL) != 0)
        return (false);
    return (true);
    
}

bool start_dinner(struct s_main *main)
{
    int i;
    pthread_t monitor_thread;

    i = 0;
    if (main->nb_philo == 1)
    {
        if (pthread_create(&main->philos[i].thread, NULL, one_philo, &main->philos[i]) != 0)
            return (false);
    }
    else {
        while (i < main->nb_philo)
        {
            if (pthread_create(&main->philos[i].thread, NULL, main_loop, &main->philos[i]) != 0)
                return (false);
            i++;
        }
    }
    if (pthread_create(&monitor_thread, NULL, monitor, main) != 0)
        return (false);
    if (!thread_join(main, monitor_thread))
        return (false);
    return (true);
}