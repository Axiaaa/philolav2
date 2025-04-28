/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcamerly <lcamerly@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 04:36:56 by lcamerly          #+#    #+#             */
/*   Updated: 2025/04/28 17:55:41 by lcamerly         ###   ########.fr       */
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