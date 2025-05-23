/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcamerly <lcamerly@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 16:58:30 by lcamerly          #+#    #+#             */
/*   Updated: 2025/05/23 22:17:51 by lcamerly         ###   ########.fr       */
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
bool	thread_join(struct s_main *main, pthread_t monitor_thread, int nb_philo)
{
	int	i;
	bool return_val;

	return_val = true;
	i = 0;
	while (i < nb_philo)
	{	
		if (pthread_join(main->philos[i].thread, NULL) != 0)
		{
			return_val = false;
			break;
		}
		i++;
	}
	if (nb_philo > 1 && pthread_join(monitor_thread, NULL))
		return_val = false;
	return (return_val);
}

bool philo_create(struct s_main *main, int *philo_started, pthread_t* monitor_thread)
{
	bool return_val;

	return_val = true;
	while (*philo_started < main->nb_philo)
	{
		if (pthread_create(&main->philos[*philo_started].thread, NULL, main_loop,
				&main->philos[*philo_started]) != 0)
		{
			set_dead(&main->philos[*philo_started]);
			return_val = false;
			(*philo_started)++;
			break;
		}
		(*philo_started)++;
	}
	if (return_val != false && pthread_create(monitor_thread, NULL, monitor, main) != 0)
	{
		set_dead(&main->philos[0]);
		return_val = false;
	}
	return (return_val);
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
	int			philo_started;
	pthread_t	monitor_thread;
	bool		return_val;

	philo_started = 0;
	return_val = true;
	if (main->nb_philo == 1)
	{
		if (pthread_create(&main->philos[philo_started].thread, NULL,
				one_philo, &main->philos[philo_started]) != 0)
			return_val = false;
		if (pthread_join(main->philos[philo_started].thread, NULL) != 0)
			return_val = false;
		return (return_val);
	}
	else
		return_val = philo_create(main, &philo_started, &monitor_thread);
	if (!thread_join(main, monitor_thread, philo_started))
		return_val = false;
	return (return_val);
}
