/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcamerly <lcamerly@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 04:32:34 by lcamerly          #+#    #+#             */
/*   Updated: 2025/04/28 17:56:16 by lcamerly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

#include <bits/pthreadtypes.h>
#include <pthread.h>
#include <stdbool.h>
#include <stdio.h>


bool init_everything(struct s_main *main, int ac, char **av)
{
    if (init_main_struct(main, ac, av) || 
        init_forks(main) != 0 ||
        init_philosophers(main->philos, main->forks, main))
        return (true); 
    return false;
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
    {
        printf("The arguments are incorrect !\n");
        return 1;
    }
    main.philos = philos;
    main.forks = forks;
    if (init_everything( &main, ac, av))
    {
        printf("Error during the init\n");
        return 1;
    }
    if (start_dinner(&main))
    {
        printf("Error during the simulation\n");
        return 1;
    }
}