/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcamerly <lcamerly@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 17:16:48 by lcamerly          #+#    #+#             */
/*   Updated: 2025/04/28 17:31:16 by lcamerly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"


void *monitor(void *main_ptr)
{
    struct s_main *main;
    main = (struct s_main *)main_ptr;
    t_philo *philo;
    int i;

    i = 0;
    while (1)
    {
        while (i < main->nb_philo)
        {
            philo = &main->philos[i];
            if (is_dead(philo) || is_full(philo))
            {
                main->exit = true;
                return NULL;
            }
            i++;
        }
        i = 0;
    }
    return (NULL);
}

