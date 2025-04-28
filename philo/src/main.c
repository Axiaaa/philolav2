/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcamerly <lcamerly@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 04:32:34 by lcamerly          #+#    #+#             */
/*   Updated: 2025/04/28 10:56:41 by lcamerly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

#include <bits/pthreadtypes.h>
#include <pthread.h>
#include <stdbool.h>
#include <stdio.h>

void init_main_struct(struct s_main *main, t_philo *philos, int ac, char **av)
{
    int i;

    i = 0;
    main->nb_philo = strtolong(av[1]);
    if (ac == 6)
        main->nb_eat = strtolong(av[5]);
    else
        main->nb_eat = -1;
    main->philos = philos;
    pthread_mutex_init(&main->lock_dead, NULL);
    pthread_mutex_init(&main->lock_eat, NULL);
    pthread_mutex_init(&main->lock_print, NULL);
    main->exit = false;
}

void init_philosophers(t_philo *philos, t_fork *forks, struct s_main *main)
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
        mutex_init(philos);
        i++;
    }
}


int main(int ac, char **av)
{
    struct s_main main;
    t_philo philos[200];
    t_fork forks[200];

    if (ac < 5 || ac > 6)
    {
        printf("The number of arg is incorrect !");
        return 1;
    }
    if (!parsing(ac, av))
        return 1;
    init_main_struct(&main, philos, ac, av);
    init_philosophers(philos, forks, &main);
}