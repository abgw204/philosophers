#include "philo.h"

/* FIX 2 ISSUES
*
* Monitor thread killing unnecessarily or not killing when it should
* Not printing sleeping and thinking after last meal (THIS MAKES NO FUCKING SENSE)
*
*/


long	gettime()
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL))
		simulation_error("Function gettimeofday failed");
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void	clean_philo(t_table **table)
{
	int	i;

	i = -1;
	while (++i < (*table)->philo_nbr)
	{
		pthread_mutex_destroy(&(*table)->philos[i].philo_mutex);
	}
	free((*table)->philos);
	free((*table)->forks);
}

void	clean(t_table **table)
{
	int	i;

	i = -1;
	while (++i < (*table)->philo_nbr)
	{
		pthread_mutex_destroy(&(*table)->forks[i].fork);
	}
	pthread_mutex_destroy(&(*table)->write_mutex);
	pthread_mutex_destroy(&(*table)->table_mutex);
	clean_philo(table);
}

void	isleep(long time)
{
	long	start;

	time = time / 1e3;
	start = gettime() + time;
	while (gettime() < start);
}

void	write_status(philo_sts status, t_philo *philo)
{
	long	elapsed;

	elapsed = gettime() - philo->table->start_simulation;
	// remove this
	if (get_bool(&philo->table->table_mutex, &philo->full))
		return ;
	pthread_mutex_lock(&philo->table->write_mutex);
	printf("%-6ld %d ", elapsed, philo->id);
	if (status == EATING)
		printf("is eating\n");
	else if (status == TAKE_FIRST_FORK
			|| status == TAKE_SECOND_FORK)
		printf("has taken a fork\n");
	else if (status == SLEEPING)
		printf("is sleeping\n");
	else if(status == THINKING)
		printf("is thinking\n");
	else if (status == DIED)
		printf("is dead\n");
	pthread_mutex_unlock(&philo->table->write_mutex);
}

void	thinking(t_philo *philo)
{
	write_status(THINKING, philo);
}

void	sleeping(t_philo *philo)
{
	write_status(SLEEPING, philo);
	isleep(philo->table->time_to_sleep);
}

bool	is_philo_gone(t_philo *philo)
{
	long	elapsed;
	long	time_to_die;

	if (get_bool(&philo->philo_mutex, &philo->full))
		return (false);
	elapsed = gettime() - get_long(&philo->philo_mutex, &philo->last_meal_time);
	time_to_die = philo->table->time_to_die;
	return (elapsed > time_to_die);
}

bool	everyone_is_full(t_table *table)
{
	int		i;
	long	j;

	i = -1;
	j = 0;
	while (++i < table->philo_nbr)
	{
		if (table->philos[i].full)
			j++;
	}
	return (j == table->philo_nbr);

}

void	*monitor_function(void *data)
{
	t_table *table;
	int		i;

	table = (t_table *)data;
	while (!all_threads_running(&table->table_mutex, &table->threads_running, table->philo_nbr))
		;
	while (!simulation_finished(table))
	{
		i = -1;
		while (++i < table->philo_nbr && !simulation_finished(table))
		{
			if (is_philo_gone(table->philos + i))
			{
				set_bool(&table->table_mutex, &table->end_simulation, true);
				write_status(DIED, &table->philos[i]);
				clean(&table);
				exit(0);
				return (NULL);
			}
		}
		if (everyone_is_full(table))
			return (NULL);
	}
	return (NULL);
}

void	eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->first_fork->fork);
	write_status(TAKE_FIRST_FORK, philo);
	pthread_mutex_lock(&philo->second_fork->fork);
	write_status(TAKE_SECOND_FORK, philo);
	set_long(&philo->philo_mutex, &philo->last_meal_time, gettime());
	write_status(EATING, philo);
	increment_long(&philo->philo_mutex, &philo->meals_counter);
	if (get_long(&philo->table->table_mutex, &philo->meals_counter)
		== philo->table->meals_limit)
		set_bool(&philo->table->table_mutex, &philo->full, true);
	isleep(philo->table->time_to_eat);
	pthread_mutex_unlock(&philo->first_fork->fork);
	pthread_mutex_unlock(&philo->second_fork->fork);
}

void	*dinner(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	wait_all_threads(philo->table);
	set_long(&philo->philo_mutex, &philo->last_meal_time, gettime());
	increment_long(&philo->table->table_mutex, &philo->table->threads_running);
	while (!simulation_finished(philo->table))
	{
		eat(philo);
		sleeping(philo);
		thinking(philo);
		if (get_long(&philo->table->table_mutex, &philo->meals_counter)
			== philo->table->meals_limit)
			break ;
	}
	return (NULL);
}

void	thread_create(pthread_t *thread, void *(func)(void *), void *data)
{
	if (pthread_create(thread, NULL, func, data) != 0)
		simulation_error("A Thread failed to be created!\n");
}

void	simulation_start(t_table *table)
{
	int	i;

	i = -1;
	if (table->meals_limit == 0)
		return ;
	else if (table->philo_nbr == 1)
		; // TODO
	else
		while (++i < table->philo_nbr)
			thread_create(&table->philos[i].thread_id, &dinner,
					&table->philos[i]);
	//thread_create(&table->monitor_thread, &monitor_function, table);
	table->start_simulation = gettime();
	i = -1;
	set_bool(&table->table_mutex, &table->all_threads_ready, true);
	//pthread_join(table->monitor_thread, NULL);
	while (++i < table->philo_nbr)
		pthread_join(table->philos[i].thread_id, NULL);
	//set_bool(&table->table_mutex, &table->end_simulation, true);
	clean(&table);
}

void	assign_forks(t_philo *philo, t_fork *forks, int i)
{
	int	philo_nbr;

	philo_nbr = (int)philo->table->philo_nbr;
	if (philo->id % 2 == 0)
	{
		philo->first_fork = &forks[i];
		philo->second_fork = &forks[(i + 1) % philo_nbr];
	}
	else
	{
		philo->first_fork = &forks[(i + 1) % philo_nbr];
		philo->second_fork = &forks[i];
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
		table->philos[i].full = false;
		table->philos[i].table = table;
		table->philos[i].last_meal_time = 0;
		pthread_mutex_init(&table->philos[i].philo_mutex, NULL);
		assign_forks(&philo[i], table->forks, i);
	}
}

void	data_init(t_table *table)
{
	int	i;

	i = -1;
	table->end_simulation = false;
	table->all_threads_ready = false;
	table->threads_running = 0;
	pthread_mutex_init(&table->table_mutex, NULL);
	table->philos = safe_malloc(table->philo_nbr * sizeof(t_philo));
	table->forks = safe_malloc(table->philo_nbr * sizeof(t_fork));
	pthread_mutex_init(&table->write_mutex, NULL);
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
		simulation_error("Wrong input! Try:\n./philo 5 400 150 150");
	parse_input(&table, av);
	data_init(&table);
	simulation_start(&table);
	return (0);
}
