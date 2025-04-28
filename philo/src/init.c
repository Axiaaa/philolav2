/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcamerly <lcamerly@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 10:48:05 by lcamerly          #+#    #+#             */
/*   Updated: 2025/04/28 17:57:03 by lcamerly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"
#include <stdbool.h>
#include <stdio.h>

bool mutex_init(t_philo *philo)
{
    if (pthread_mutex_init(philo->lock_eat, NULL) != 0)
        return false;
    if (pthread_mutex_init(philo->lock_dead, NULL) != 0)
        return false;
    if (pthread_mutex_init(philo->lock_print, NULL) != 0)
        return false;
    return true;
}

bool init_main_struct(struct s_main *main, int ac, char **av)
{
    main->nb_philo = strtolong(av[1]);
    if (ac == 6)
        main->nb_eat = strtolong(av[5]);
    else
        main->nb_eat = -1;
    main->exit = false;
    if (pthread_mutex_init(&main->lock_dead, NULL) != 0 ||
        pthread_mutex_init(&main->lock_print, NULL) != 0 ||
        pthread_mutex_init(&main->lock_eat, NULL) != 0)
        return false;
    return true;
}

bool init_philosophers(t_philo *philos, t_fork *forks, struct s_main *main)
{
    int i;

    i = -1;
    while (++i < main->nb_philo)
    {
        philos[i].id = i + 1 ;
        philos[i].eat_count = 0;
        philos[i].last_eat_time = 0;
        philos[i].is_eating = false;
        philos[i].is_dead = false;
        philos[i].forklock_r = &forks[i];
        philos[i].forklock_l = &forks[(i + 1) % main->nb_philo];
        philos[i].lock_eat = &main->lock_eat;
        philos[i].lock_dead = &main->lock_dead;
        philos[i].lock_print = &main->lock_print;
        if (mutex_init(philos) != 0)
            return false;
        i++;
    }
    return true;
}

bool init_forks(struct s_main *main)
{
    int i;

    i = -1;
    while (++i < main->nb_philo)
        if (pthread_mutex_init(main->forks[i].mutex, NULL) != 0)
            return 1;
    return 0;
}