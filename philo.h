#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <pthread.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdbool.h>

typedef struct mutexes
{
	pthreads_mutex_t	
}	t_mutex;

typedef struct philoAndForks
{
    pthread_t   philo;
	int	        philoId;
	int	        fork;
	struct      philoAndForks	*next;
	struct      philoAndForks	*prev;
}	t_philo;

void    appendPhilo(t_philo **lst, t_philo *new);
t_philo *newPhilo(int philoId, int fork);
int      list_size(t_philo *lst);

#endif
