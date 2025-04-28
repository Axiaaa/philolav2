/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcamerly <lcamerly@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 16:58:30 by lcamerly          #+#    #+#             */
/*   Updated: 2025/04/28 17:52:03 by lcamerly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"
#include <pthread.h>

void *main_loop(void *philo_ptr)
{
    t_philo *philo;

    philo = (t_philo *)philo_ptr;
    while (!is_dead(philo) && !is_full(philo))
    {
        eat(philo);
        philo_sleep(philo);
        think(philo);
    }
    return (NULL);
}

bool start_dinner(struct s_main *main)
{
    int i;
    pthread_t monitor_thread;

    i = 0;
    while (i < main->nb_philo)
    {
        if (pthread_create(&main->philos[i].thread, NULL, main_loop, &main->philos[i]) != 0)
            return (false);
        i++;
    }
    if (pthread_create(&monitor_thread, NULL, monitor, main) != 0)
        return (false);
    if (pthread_join(monitor_thread, NULL) != 0)
        return (false);
    i = 0;
    while (i < main->nb_philo)
    {
        if (pthread_join(main->philos[i].thread, NULL) != 0)
            return (false);
        i++;
    }
    return (true);
}