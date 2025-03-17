#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <pthread.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdbool.h>
# include <sys/time.h>

# define RESET        "\033[0m"
# define BOLD_RED     "\033[1;31m"
# define BOLD_GREEN   "\033[1;32m"
# define BOLD_YELLOW  "\033[1;33m"
# define BOLD_BLUE    "\033[1;34m"
# define BOLD_MAGENTA "\033[1;35m"
# define BOLD_CYAN    "\033[1;36m"
# define BOLD_WHITE   "\033[1;37m"

typedef struct	s_table t_table;

typedef struct s_forks
{
	pthread_mutex_t	fork;
	int		fork_id;
}	t_fork;

typedef struct s_philo
{
	int	        id;
	long		meals_counter;
	bool		full;
	long		last_meal_time;
	t_fork		*first_fork;
	t_fork		*second_fork;
    	pthread_t   	thread_id;
	t_table		*table;
}	t_philo;

struct	s_table
{
	long	philo_nbr;
	long	time_to_die;
	long	time_to_eat;
	long	time_to_sleep;
	long	meals_limit;
	long	start_simulation;
	bool	end_simulation;
	bool	all_threads_ready;
	pthread_mutex_t	table_mutex;
	t_philo	*philos;
	t_fork	*forks;
};

void	parse_input(t_table *table, char **av);
void	simulation_error(int error);
void	*safe_malloc(size_t bytes);
void	set_bool(pthread_mutex_t *mutex, bool *variable, bool value);
bool	get_bool(pthread_mutex_t *mutex, bool *variable);
void	set_long(pthread_mutex_t *mutex, long *variable, long value);
bool	get_long(pthread_mutex_t *mutex, long *variable);
bool	simulation_finished(t_table *table);
void	wait_all_threads(t_table *table);
#endif
