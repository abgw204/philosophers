#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <pthread.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdbool.h>

# define RESET        "\033[0m"
# define BOLD_RED     "\033[1;31m"
# define BOLD_GREEN   "\033[1;32m"
# define BOLD_YELLOW  "\033[1;33m"
# define BOLD_BLUE    "\033[1;34m"
# define BOLD_MAGENTA "\033[1;35m"
# define BOLD_CYAN    "\033[1;36m"
# define BOLD_WHITE   "\033[1;37m"

typedef struct s_forks
{
	pthread_mutex_t	fork;
	int		fork_id;
}	t_fork;

typedef struct philoAndForks
{
    	pthread_t   	philo;
	int	        philoId;
	struct      philoAndForks	*next;
	struct      philoAndForks	*prev;
}	t_philo;

typedef struct	s_table
{
	long	philo_nbr;
	long	time_to_die;
	long	time_to_eat;
	long	time_to_sleep;
	long	meals_limit;
	long	start_simulation;
	bool	end_simulation;
	t_philo	*philosophers;
	t_fork	*forks;
}	t_table;

void	parse_input(t_table *table, char **av);
void    appendPhilo(t_philo **lst, t_philo *new);
t_philo *newPhilo(int philoId);
int      list_size(t_philo *lst);
void	simulation_error(int error);

#endif
