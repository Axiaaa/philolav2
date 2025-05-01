/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcamerly <lcamerly@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 04:49:11 by lcamerly          #+#    #+#             */
/*   Updated: 2025/05/01 15:51:22 by lcamerly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdbool.h>
#include <pthread.h>

# ifndef DEBUG
#  define DEBUG 0
# endif

# define PHILO_MAX 200

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
    pthread_mutex_t mutex;
} t_fork;

typedef struct s_philo
{
    int id;
    int eat_count;
    int must_eat_count;
    int time_to_die;
    int time_to_eat;
    int time_to_sleep;
    int nbr_philo;
    
    long last_eat_time;
    long start_time;
    
    bool is_eating;
    bool *is_dead;
    bool is_full;
    
    t_fork *fork_r;
    t_fork *fork_l;
    pthread_mutex_t *lock_eat;
    pthread_mutex_t *lock_dead;
    pthread_mutex_t *lock_print;

    pthread_t thread;
} t_philo;


struct s_main {
    
    t_philo *philos;
    t_fork *forks;
    
    int nb_philo;
    int nb_eat;
    
    long start_time;

    bool exit;
    
    pthread_mutex_t lock_nb_eat;
    pthread_mutex_t lock_eat;
    pthread_mutex_t lock_dead;
    pthread_mutex_t lock_print;

    pthread_t monitor_thread;
    
};

bool is_nbr(char *str);
bool is_dead(t_philo *philo);
bool init_main_struct(struct s_main *main, int ac, char **av);
bool init_philosophers(t_philo *philos, t_fork *forks, struct s_main *main);
bool init_forks(struct s_main *main);
bool init_parsing(struct s_main *main, int ac, char **av);
bool mutex_init(t_philo *philo);
bool parsing(int ac, char **av);
bool start_dinner(struct s_main *main);

long    gettime(int time_code, t_philo *philo);
long    strtolong(char *str);

void	ft_sleep(long time, t_philo *philo);

void eat(t_philo *philo);
void exit_if_all_full(struct s_main *main, int finished_eating);
void kill_mutexes(struct s_main *main);
void philo_sleep(t_philo *philo);
void printfilo(int status, t_philo *philo);
void think(t_philo *philo);
void set_dead(t_philo *philo);

void *one_philo(void *philo_ptr);
void *monitor(void *main_ptr);
void *main_loop(void *philo);

#endif