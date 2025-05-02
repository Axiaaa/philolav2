/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcamerly <lcamerly@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 17:16:48 by lcamerly          #+#    #+#             */
/*   Updated: 2025/05/02 11:53:03 by lcamerly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

/**
* @brief Check if the philosopher is dead.
* 
* @param philo Pointer to the philosopher structure.
*
* @return true if the philosopher is alive, false if dead.
*/
bool	check_death_time(t_philo *philo)
{
	pthread_mutex_lock(philo->lock_eat);
	if (gettime(MILLISECOND, philo) - philo->last_eat_time > philo->time_to_die)
	{
		printfilo(DIED, philo);
		pthread_mutex_unlock(philo->lock_eat);
		pthread_mutex_lock(philo->lock_dead);
		*philo->is_dead = true;
		pthread_mutex_unlock(philo->lock_dead);
		return (false);
	}
	pthread_mutex_unlock(philo->lock_eat);
	return (true);
}

/**
* @brief Check if the philosopher is full.
*
* @param philo Pointer to the philosopher structure.
* @param main Pointer to the main structure.
*
* @return true if the philosopher is not full, false if full.
*/
bool	check_philo_full(t_philo *philo, struct s_main *main)
{
	bool	is_full;
	bool	all_full;

	pthread_mutex_lock(philo->lock_eat);
	if (philo->eat_count >= philo->must_eat_count && !philo->is_full)
	{
		philo->is_full = true;
		is_full = true;
	}
	pthread_mutex_unlock(philo->lock_eat);
	if (is_full)
	{
		pthread_mutex_lock(&main->lock_dead);
		main->nb_eat++;
		all_full = (main->nb_eat == main->nb_philo);
		pthread_mutex_unlock(&main->lock_dead);
		if (all_full)
		{
			pthread_mutex_lock(philo->lock_dead);
			*philo->is_dead = true;
			pthread_mutex_unlock(philo->lock_dead);
			return (false);
		}
	}
	return (true);
}

/**
* @brief Monitor function to check the status of philosophers.
*
* @param main_ptr Pointer to the main structure.
*
* @details This function is executed by the monitor thread. It checks
* if any philosopher has died or if all philosophers have eaten enough.
* It runs in a loop until all philosophers are full or one of them dies.
* @return NULL
*/
void	*monitor(void *main_ptr)
{
	struct s_main	*main;
	t_philo			*philo;
	int				i;

	main = (struct s_main *)main_ptr;
	i = 0;
	while (main->nb_philo > 1)
	{
		while (i < main->nb_philo)
		{
			philo = &main->philos[i];
			if (!check_death_time(philo))
				return (NULL);
			if (philo->must_eat_count != -1)
			{
				if (!check_philo_full(philo, main))
					return (NULL);
			}
			i++;
		}
		i = 0;
	}
	return (NULL);
}
