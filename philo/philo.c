#include "philo.h"

long	gettime()
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL))
		simulation_error("Function gettimeofday failed");
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
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

	if (philo->full)
		return ;
	pthread_mutex_lock(&philo->table->write_mutex);
	printf("%-6ld %d ", elapsed, philo->id);
	if (status == EATING)
		printf("is eating\n");
	else if (status == TAKE_FIRST_FORK
			|| status == TAKE_SECOND_FORK)
		printf("has taken a fork\n");
	pthread_mutex_unlock(&philo->table->write_mutex);
}

void	sleeping(t_philo *philo)
{
	usleep(philo->table->time_to_sleep);
}

void	eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->first_fork->fork);
	write_status(TAKE_FIRST_FORK, philo);
	pthread_mutex_lock(&philo->second_fork->fork);
	write_status(TAKE_SECOND_FORK, philo);
	set_long(&philo->philo_mutex, &philo->last_meal_time, gettime());
	if (philo->table->meals_limit > 0
		&& philo->meals_counter == philo->table->meals_limit)
		set_bool(&philo->philo_mutex, &philo->full, true);
	write_status(EATING, philo);
	isleep(philo->table->time_to_eat);
	philo->meals_counter++;
	pthread_mutex_unlock(&philo->first_fork->fork);
	pthread_mutex_unlock(&philo->second_fork->fork);
}

void	*dinner(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	wait_all_threads(philo->table);
	while (!simulation_finished(philo->table))
	{
		if (get_bool(&philo->table->table_mutex, &philo->full))
			break ;
		eat(philo);
		//sleeping(philo);
		// think
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
	table->start_simulation = gettime();
	set_bool(&table->table_mutex, &table->all_threads_ready, true);
	i = -1;
	while (++i < table->philo_nbr)
		pthread_join(table->philos[i].thread_id, NULL);
	// end stuff TODO
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
