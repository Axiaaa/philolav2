/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcamerly <lcamerly@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 04:36:56 by lcamerly          #+#    #+#             */
/*   Updated: 2025/05/02 11:45:05 by lcamerly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"
#include <limits.h>
#include <stdio.h>

/**
 * @brief Check if the string is a number.
 *
 * @param str The string to check.
 *
 * @return true if the string is a number, false otherwise.
*/
bool	is_nbr(char *str)
{
	int	i;

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

/**
* @brief Convert a string to a long integer.
*
* @param str The string to convert.
*
* @return The converted long integer.
*/
long	strtolong(char *str)
{
	long	result;
	int		i;

	i = 0;
	result = 0;
	while (str[i])
	{
		result = result * 10 + (str[i] - '0');
		i++;
	}
	return (result);
}

/**
 * @brief Check if the input arguments are valid.
 *
 * @param ac The number of arguments.
 * @param av The array of arguments.
 *
 * @return true if the arguments are valid, false otherwise.
*/
bool	parsing(int ac, char **av)
{
	int	i;

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
		if (strtolong(av[i]) >= INT_MAX || strtolong(av[i]) <= 0)
		{
			printf("The numbers shouldn't be greater than INT_MAX nor \
					inferior to 1\n");
			return (false);
		}
		i++;
	}
	return (true);
}
