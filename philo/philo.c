#include "philo.h"

pthread_mutex_t	mutex;
void	*do_smt(void *philos)
{
	t_philo *philo;

	philo = (t_philo *)philos;
	printf("%d is sleeping\n", philo->philoId);
	pthread_mutex_lock(&mutex);
	sleep(1);
	pthread_mutex_unlock(&mutex);
	printf("%d is dead\n", philo->philoId);
	return (NULL);
}

void	destroy_list(t_philo **philos)
{
	t_philo	*aux;

	if (!*philos)
		return ;
	while ((*philos)->philoId <= 1)
	{
		aux = (*philos)->prev;
		free(philos);
		*philos = aux;
	}
	*philos = NULL;
}

void	create_philos(t_philo *philo)
{
	int	i;

	i = 0;
	while (i < list_size(philo))
	{
		if (pthread_create(&philo->philo, NULL, &do_smt, philo) != 0)
			destroy_list(&philo);
		philo = philo->next;
	}
}

t_philo	*create_list(int ac, char **av)
{
	(void)ac;
	t_philo	*philo_list;
	int		philos;
	int 	i;

	philos = atoi(av[1]);
	i = 1;
	philo_list = NULL;
	while (philos--)
	{
		appendPhilo(&philo_list, newPhilo(i, i));
		i++;
	}
	create_philos(philo_list);
	return (philo_list);
}

void	init_threads(t_philo *philos)
{
	int i;

	i = list_size(philos);
	while (i--)
	{
		pthread_join(philos->philo, NULL);
		philos = philos->next;
	}
}

int main(int ac, char **av)
{
	t_philo				*philos;

	pthread_mutex_init(&mutex, NULL);
	if (ac != 2)
		return (1);
	philos = NULL;
	pthread_mutex_init(&mutex, NULL);
	philos = create_list(ac, av);
	init_threads(philos);
	return (0);
}
