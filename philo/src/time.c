/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcamerly <lcamerly@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 10:17:54 by lcamerly          #+#    #+#             */
/*   Updated: 2025/04/29 16:31:27 by lcamerly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"
#include <sys/time.h> 
#include <stdio.h>
#include <unistd.h>

long    gettime(int time_code)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL))
		return (-1);
	if (MILLISECOND == time_code)
		return (tv.tv_sec * 1e3 + tv.tv_usec / 1e3);
	else if (MICROSECOND == time_code)
		return (tv.tv_sec * 1e6 + tv.tv_usec);
    return (69);
}

int ft_sleep(long time)
{
    long start_time;

    start_time = gettime(MILLISECOND);
    while (gettime(MILLISECOND) - start_time < time)
        usleep(100);
    return (0);
}