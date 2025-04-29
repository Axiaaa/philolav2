/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcamerly <lcamerly@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 04:36:56 by lcamerly          #+#    #+#             */
/*   Updated: 2025/04/29 20:04:13 by lcamerly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"
#include <limits.h>
#include <stdio.h>
#include <stdbool.h>

bool is_nbr(char *str)
{
    int i;

    i = 0;
    while (str[i])
    {
        if (str[i] >= '0' && str[i] <= '9')
            i++;
        else
            return (false);
    }
    return (true);
}

long strtolong(char *str)
{
    long result;
    int i;

    i = 0;
    result = 0;
    while (str[i])
    {
        result = result * 10 + (str[i] - '0');
        i++;
    }
    return (result);
}

bool parsing(int ac, char **av)
{
    int i;

    i = 1;

    if (strtolong(av[1]) > PHILO_MAX)
    {
        printf("We said no more than %d philos !\n", PHILO_MAX);
        return (false);
    }
    while (i < ac)
    {
        if (!is_nbr(av[i]))
        {
            printf("You should only input numbers\n");
            return (false);
        }
        if (strtolong(av[i]) >= INT_MAX || strtolong(av[i]) < 0)
        {
            printf("The numbers shouldn't be greater than INT_MAX or inferior to 0\n");
            return (false);
        }
        i++;
    }
    return (true);
}