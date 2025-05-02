/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcamerly <lcamerly@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 10:17:54 by lcamerly          #+#    #+#             */
/*   Updated: 2025/05/02 08:47:45 by lcamerly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"
#include <sys/time.h> 
#include <stdio.h>
#include <unistd.h>

/**
 * @brief Get the current system time in specified units.
 *
 * @param time_code Specifies the time unit to return:
 *                  - MILLISECOND: returns time in milliseconds
 *                  - MICROSECOND: returns time in microseconds
 *
 * @return long The current time in the specified unit,
 * or -1 if an error occurred.
*/
long	gettime(int time_code, t_philo *philo)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL))
	{
		printf("Error in gettime: gettimeofday failed\n");
		if (philo)
			set_dead(philo);
		return (-1);
	}
	if (MILLISECOND == time_code)
		return (tv.tv_sec * 1e3 + tv.tv_usec / 1e3);
	else if (MICROSECOND == time_code)
		return (tv.tv_sec * 1e6 + tv.tv_usec);
	else
	{
		printf("Error in gettime: invalid time_code\n");
		if (philo)
			set_dead(philo);
		return (-1);
	}
}

/**
 * @brief Sleep for a specified amount of time.
 *
 * @param time The time to sleep in milliseconds.
 * @param philo Pointer to philosopher struct.
 *
 * @returns None.
 */
void	ft_sleep(long time, t_philo *philo)
{
	time += gettime(MILLISECOND, philo);
	while (gettime(MILLISECOND, philo) < time)
	{
		if (usleep(100) < 0)
		{
			printf("Error in ft_sleep: usleep failed\n");
			if (philo)
				set_dead(philo);
			return ;
		}
	}
}
