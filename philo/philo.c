#include "philo.h"

void	*do_smt(void *smt)
{
	smt = smt;
	printf("oi\n");
	return (NULL);
}

void	thread_create(pthread_t *thread, void *(func)(void *), void *data)
{
	if (pthread_create(thread, NULL, func, data) != 0)
		simulation_error(1);
}

void	simulation_start(t_table *table)
{
	int	i;

	i = -1;
	if (table->meals_limit == 0)
		return ;
	else if (table->philo_nbr == 1)
		;// oi
	else
	{
		while (++i < table->philo_nbr)
			thread_create(&table->philos[i].thread_id, &do_smt, &table->philos[i]);
	}
}

void	assign_forks(t_philo *philo, t_fork *forks, int i)
{
	int	philo_nbr;

	philo_nbr = philo->table->philo_nbr;
	if (philo->id % 2 == 0)
	{
		philo->first_fork = &forks[i];
		philo->second_fork = &forks[(i + 1) % philo_nbr];
	}
	else
	{
		philo->second_fork = &forks[i];
		philo->first_fork = &forks[(i + 1) % philo_nbr];
	}
}

void	philo_init(t_table *table)
{
	t_philo	*philo;
	int	i;

	i = -1;
	philo = table->philos;
	while (++i < table->philo_nbr)
	{
		table->philos[i].id = i + 1;
		table->philos[i].meals_counter = 0;
		table->philos[i].table = table;
		assign_forks(&philo[i], table->forks, i);
	}
}

void	data_init(t_table *table)
{
	int	i;

	i = -1;
	table->end_simulation = false;
	table->philos = safe_malloc(table->philo_nbr * sizeof(t_philo));
	table->forks = safe_malloc(table->philo_nbr * sizeof(t_fork));
	while (++i < table->philo_nbr)
	{
		pthread_mutex_init(&table->forks[i].fork, NULL);
		table->forks[i].fork_id = i;
	}
	philo_init(table);
}

int main(int ac, char **av)
{
	t_table	table;

	if (ac != 5 && ac != 6)
		simulation_error(1);
	parse_input(&table, av);
	data_init(&table);
	simulation_start(&table);
	return (0);
}
