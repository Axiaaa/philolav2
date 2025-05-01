/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcamerly <lcamerly@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 10:48:05 by lcamerly          #+#    #+#             */
/*   Updated: 2025/05/01 15:51:59 by lcamerly         ###   ########.fr       */
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
    (void)ac;
    main->nb_philo = strtolong(av[1]);
    main->nb_eat = 0;
    main->exit = false;
    main->start_time = gettime(MILLISECOND, NULL);
    if (main->start_time == -1)
        return false;
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
        philos[i].is_eating = false;
        philos[i].is_dead = &main->exit;
        philos[i].is_full = false;
        philos[i].last_eat_time = main->start_time;
        philos[i].start_time = main->start_time;
        philos[i].fork_l = &forks[i];
        if (i < main->nb_philo - 1)
            philos[i].fork_r = &forks[i + 1];
        else
            philos[i].fork_r = &forks[0];
        philos[i].lock_eat = &main->lock_eat;
        philos[i].lock_dead = &main->lock_dead;
        philos[i].lock_print = &main->lock_print;
        philos[i].nbr_philo = main->nb_philo;
        if (!mutex_init(philos))
            return false;
    }
    return true;
}

bool init_forks(struct s_main *main)
{
    int i;

    i = -1;
    while (++i < main->nb_philo)
    {
        main->forks[i].id = i + 1;
        if (pthread_mutex_init(&main->forks[i].mutex, NULL) != 0)
            return false;
    }
    return true;
}

bool init_parsing(struct s_main *main, int ac, char **av)
{
    int i;

    i = -1;
    while (++i < main->nb_philo)
    {
        main->philos[i].time_to_die = strtolong(av[2]);
        main->philos[i].time_to_eat = strtolong(av[3]);
        main->philos[i].time_to_sleep = strtolong(av[4]);
        if (ac == 6)
            main->philos[i].must_eat_count = strtolong(av[5]);
        else
            main->philos[i].must_eat_count = -1;
    }
    return true;
}