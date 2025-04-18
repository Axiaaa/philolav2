/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcamerly <lcamerly@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 04:49:11 by lcamerly          #+#    #+#             */
/*   Updated: 2025/04/18 05:24:36 by lcamerly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdbool.h>
#include <pthread.h>

bool parsing(int ac, char **av);
long strtolong(char *str);
bool is_nbr(char *str);

typedef struct s_fork
{
    int id;
    pthread_mutex_t *mutex;
} t_fork;

typedef struct s_philo
{
    int id;
    int eat_count;
    
    long last_eat_time;

    bool *is_eating;
    bool *is_dead;

    t_fork *forklock_r;
    t_fork *forklock_l;
    pthread_mutex_t *lock_eat;
    pthread_mutex_t *lock_dead;
    pthread_mutex_t *lock_print;
} t_philo;


struct s_main {

    t_philo *philos;
    
    int nb_philo;
    int time_to_die;
    int time_to_eat;
    int time_to_sleep;
    int nb_eat;

    bool exit;
    
    pthread_mutex_t lock_eat;
    pthread_mutex_t lock_dead;
    pthread_mutex_t lock_print;
    
};

#endif