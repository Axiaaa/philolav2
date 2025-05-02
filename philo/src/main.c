/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcamerly <lcamerly@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 04:32:34 by lcamerly          #+#    #+#             */
/*   Updated: 2025/05/02 11:55:01 by lcamerly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"
#include <stdio.h>

/**
 * @brief Print philosopher information.
 *
 * @param philo Pointer to the philosopher structure.
 *
 * @details This function prints the information of a philosopher.
 * It is used for debugging purposes.
 *
 * @return None
*/
void	print_philo_info(t_philo *philo)
{
	printf("Philosopher %d:\n", philo->id);
	printf("  - eat_count: %d\n", philo->eat_count);
	printf("  - last_eat_time: %ld\n", philo->last_eat_time);
	printf("  - start_time: %ld\n", philo->start_time);
	printf("  - left_fork: %d\n", philo->fork_l->id);
	printf("  - right_fork: %d\n", philo->fork_r->id);
	printf("  - time_to_die: %d ms\n", philo->time_to_die);
	printf("  - time_to_eat: %d ms\n", philo->time_to_eat);
	printf("  - time_to_sleep: %d ms\n", philo->time_to_sleep);
	printf("  - is_dead: %d\n", *philo->is_dead);
	printf("  - is_full: %d\n", philo->is_full);
	printf("  - is_eating: %d\n", philo->is_eating);
	printf("  - must_eat_count: %d\n", philo->must_eat_count);
}

/**
 * @brief Print debug information.
 *
 * @param main Pointer to the main structure.
 *
 * @details This function prints debug information about the philosophers
 * and forks. It is used for debugging purposes.
 *
 * @return None
*/
void	printdebug(struct s_main *main)
{
	int	i;

	i = 0;
	printf("Initialization successful\n");
	printf("Philosophers:\n");
	while (i < main->nb_philo)
	{
		print_philo_info(&main->philos[i]);
		i++;
	}
	i = 0;
	printf("Forks:\n");
	while (i < main->nb_philo)
	{
		printf(" - Fork %d: addr=%p\n",
			main->forks[i].id, &main->forks[i].mutex);
		i++;
	}
}

/**
 * @brief Initialize all components of the program.
 *
 * @param main Pointer to the main structure.
 * @param ac Number of arguments.
 * @param av Array of arguments.
 *
 * @return true if initialization is successful, false otherwise.
*/
bool	init_everything(struct s_main *main, int ac, char **av)
{
	if (!init_main_struct(main, av)
		|| !init_forks(main)
		|| !init_philosophers(main->philos, main->forks, main)
		|| !init_parsing(main, ac, av))
		return (false);
	if (DEBUG)
		printdebug(main);
	return (true);
}

/**
 * @brief Start the dinner simulation.
 *
 * @param main Pointer to the main structure.
 *
 * @return true if the dinner started successfully, false otherwise.
*/
int	main(int ac, char **av)
{
	struct s_main	main;
	t_philo			philos[PHILO_MAX];
	t_fork			forks[PHILO_MAX];

	if (ac < 5 || ac > 6)
	{
		printf("The number of arg is incorrect !");
		return (1);
	}
	if (!parsing(ac, av))
	{
		printf("The arguments are incorrect !\n");
		return (1);
	}
	main.philos = philos;
	main.forks = forks;
	if (!init_everything(&main, ac, av))
		return (1);
	if (!start_dinner(&main))
	{
		kill_mutexes(&main);
		printf("Error while starting the dinner !\n");
		return (1);
	}
	return (0);
}
