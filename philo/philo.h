/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gada-sil <gada-sil@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 18:03:54 by gada-sil          #+#    #+#             */
/*   Updated: 2025/04/09 18:03:56 by gada-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <pthread.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdbool.h>
# include <sys/time.h>

typedef struct s_table	t_table;

typedef enum philo_status
{
	EATING,
	THINKING,
	SLEEPING,
	TAKE_FIRST_FORK,
	TAKE_SECOND_FORK,
	DIED
}	t_philo_sts;

typedef struct s_forks
{
	pthread_mutex_t	fork;
	int				fork_id;
}	t_fork;

typedef struct s_philo
{
	int				id;
	long			meals_counter;
	bool			full;
	long			last_meal_time;
	t_fork			*first_fork;
	t_fork			*second_fork;
	pthread_t		thread_id;
	pthread_mutex_t	philo_mutex;
	t_table			*table;
}	t_philo;

struct	s_table
{
	long			philo_nbr;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	long			meals_limit;
	long			start_simulation;
	long			threads_running;
	bool			end_simulation;
	bool			all_threads_ready;
	pthread_t		monitor_thread;
	pthread_mutex_t	table_mutex;
	pthread_mutex_t	write_mutex;
	t_philo			*philos;
	t_fork			*forks;
};

void	parse_input(t_table *table, char **av);
void	simulation_error(const char *error_message);
void	*safe_malloc(size_t bytes);
void	set_bool(pthread_mutex_t *mutex, bool *variable, bool value);
bool	get_bool(pthread_mutex_t *mutex, bool *variable);
void	set_long(pthread_mutex_t *mutex, long *variable, long value);
long	get_long(pthread_mutex_t *mutex, long *variable);
bool	simulation_finished(t_table *table);
void	wait_all_threads(t_table *table);
bool	all_threads_running(pthread_mutex_t *mutex, long *threads,
			long philo_nbr);
void	increment_long(pthread_mutex_t *mutex, long *value);
void	eat(t_philo *philo);
void	sleeping(t_philo *philo);
void	thinking(t_philo *philo);
void	write_status(t_philo_sts status, t_philo *philo);
long	gettime(void);
void	isleep(long time);
void	data_init(t_table *table);
void	*monitor_function(void *data);
void	thread_create(pthread_t *thread, void *(func)(void *), void *data);
void	clean_philo(t_table **table);
void	clean(t_table **table);
void	assign_forks(t_philo *philo, t_fork *forks, int i);
void	philo_init(t_table *table);
bool	is_philo_gone(t_philo *philo);
bool	everyone_is_full(t_table *table);
void	philo_dead(t_philo *philo);

#endif
