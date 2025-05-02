/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcamerly <lcamerly@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 16:58:30 by lcamerly          #+#    #+#             */
/*   Updated: 2025/05/02 11:37:21 by lcamerly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

/**
 * @brief Function executed by the philosopher thread.
 *
 * @param philo_ptr Pointer to the philosopher struct
 *
 * @details This function is executed by each philosopher thread. It
 * alternates between eating, sleeping, and thinking.
 *
 * @return NULL
*/
void	*main_loop(void *philo_ptr)
{
	t_philo	*philo;

	philo = (t_philo *)philo_ptr;
	if (philo->id % 2 == 1)
		ft_sleep(philo->time_to_eat / 2, philo);
	while (!is_dead(philo))
	{
		eat(philo);
		philo_sleep(philo);
		think(philo);
	}
	return (NULL);
}

/**
 * @brief This function is used to join all threads.
 *
 * @param main_ptr Pointer to the main struct
 * @param monitor_thread The monitor thread
 *
 * @details This function is executed by the monitor thread. It checks
 * if any philosopher has died or if all philosophers have eaten enough.
 *
 * @return bool
*/
bool	thread_join(struct s_main *main, pthread_t monitor_thread)
{
	int	i;

	i = 0;
	while (i < main->nb_philo)
	{
		if (pthread_join(main->philos[i].thread, NULL) != 0)
			return (false);
		i++;
	}
	if (pthread_join(monitor_thread, NULL) != 0)
		return (false);
	return (true);
}

/**
 * @brief This function is used to start the dinner.
 *
 * @param main Pointer to the main struct
 *
 * @details This function creates the philosopher threads and the monitor
 * thread. It also handles the case where there is only one philosopher.
 *
 * @return bool
*/
bool	start_dinner(struct s_main *main)
{
	int			i;
	pthread_t	monitor_thread;

	i = 0;
	if (main->nb_philo == 1)
	{
		if (pthread_create(&main->philos[i].thread, NULL,
				one_philo, &main->philos[i]) != 0)
			return (false);
	}
	else
	{
		while (i < main->nb_philo)
		{
			if (pthread_create(&main->philos[i].thread, NULL, main_loop,
					&main->philos[i]) != 0)
				return (false);
			i++;
		}
	}
	if (pthread_create(&monitor_thread, NULL, monitor, main) != 0)
		return (false);
	if (!thread_join(main, monitor_thread))
		return (false);
	return (true);
}
