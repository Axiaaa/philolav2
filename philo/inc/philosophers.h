/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcamerly <lcamerly@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 04:49:11 by lcamerly          #+#    #+#             */
/*   Updated: 2025/04/28 10:54:39 by lcamerly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdbool.h>
#include <pthread.h>

enum e_time
{
    MILLISECOND = 1,
    MICROSECOND = 2
};

enum e_log
{
    TAKE_FIRST_FORK,
    TAKE_SECOND_FORK,
    EATING,
    SLEEPING,
    THINKING,
    DIED
};


typedef struct s_fork
{
    int id;
    pthread_mutex_t *mutex;
} t_fork;

typedef struct s_philo
{
    int id;
    int eat_count;
    int must_eat_count;
    int time_to_die;
    int time_to_eat;
    int time_to_sleep;
    
    long last_eat_time;
    long start_time;
    
    bool is_eating;
    bool is_dead;
    
    t_fork *forklock_r;
    t_fork *forklock_l;
    pthread_mutex_t *lock_eat;
    pthread_mutex_t *lock_dead;
    pthread_mutex_t *lock_print;
} t_philo;


struct s_main {
    
    t_philo *philos;
    
    int nb_philo;
    int nb_eat;
    
    bool exit;
    
    pthread_mutex_t lock_eat;
    pthread_mutex_t lock_dead;
    pthread_mutex_t lock_print;
    
};

bool parsing(int ac, char **av);
long strtolong(char *str);
bool is_nbr(char *str);
long gettime(int time_code);
bool is_dead(t_philo *philo);
bool is_full(t_philo *philo);
int ft_sleep(long time);
int mutex_init(t_philo *philo);

#endif