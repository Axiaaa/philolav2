/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcamerly <lcamerly@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 04:32:34 by lcamerly          #+#    #+#             */
/*   Updated: 2025/04/30 09:28:46 by lcamerly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

#include <bits/pthreadtypes.h>
#include <pthread.h>
#include <stdbool.h>
#include <stdio.h>

void printdebug(struct s_main *main)
{
    printf("Philosophers and forks initialized successfully\n");
    printf("Philosophers:\n");
    for (int i = 0; i < main->nb_philo; i++)
    {
        printf("Philosopher %d:\n", main->philos[i].id);
        printf("  - eat_count: %d\n", main->philos[i].eat_count);
        printf("  - last_eat_time: %ld\n", main->philos[i].last_eat_time);
        printf("  - start_time: %ld\n", main->philos[i].start_time);
        printf("  - left_fork: %d\n", main->philos[i].fork_l->id);
        printf("  - right_fork: %d\n", main->philos[i].fork_r->id);
        printf("  - time_to_die: %d ms\n", main->philos[i].time_to_die);
        printf("  - time_to_eat: %d ms\n", main->philos[i].time_to_eat);
        printf("  - time_to_sleep: %d ms\n", main->philos[i].time_to_sleep);
        printf("  - is_dead: %d\n", *main->philos[i].is_dead);
        printf("  - is_full: %d\n", main->philos[i].is_full);
        printf("  - is_eating: %d\n", main->philos[i].is_eating);
        printf("  - must_eat_count: %d\n", main->philos[i].must_eat_count);
    }
    printf("Forks:\n");
    for (int i = 0; i < main->nb_philo; i++)
    {
        printf("Fork %d: id = %d\n", i + 1, main->forks[i].id);
    }
}

bool init_everything(struct s_main *main, int ac, char **av)
{
    if (!init_main_struct(main, ac, av) || 
        !init_forks(main) ||
        !init_philosophers(main->philos, main->forks, main) ||
        !init_parsing(main, ac, av))
        return (false);
    if (DEBUG)
        printdebug(main);
    return true;
}


int main(int ac, char **av)
{
    struct s_main main;
    t_philo philos[PHILO_MAX];
    t_fork forks[PHILO_MAX];

    if (ac < 5 || ac > 6)
    {
        printf("The number of arg is incorrect !");
        return 1;
    }
    if (!parsing(ac, av))
    {
        printf("The arguments are incorrect !\n");
        return 1;
    }
    main.philos = philos;
    main.forks = forks;
    if (!init_everything( &main, ac, av))
        return 1;
    if (!start_dinner(&main))
    {
        kill_mutexes(&main);
        printf("Error while starting the dinner !\n");
        return 1;
    }
    return 0;
}
