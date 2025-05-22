/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gada-sil <gada-sil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 17:59:35 by gada-sil          #+#    #+#             */
/*   Updated: 2025/05/21 22:14:10 by gada-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philo.h"

static void	lonely_simulation(t_table *table)
{
	long	elapsed;

	table->start_simulation = gettime();
	elapsed = gettime() - table->start_simulation;
	pthread_mutex_lock(&table->write_mutex);
	printf("%-6ld 1 has taken a fork\n", elapsed);
	isleep(table->time_to_die * 1e3);
	printf("%-6ld 1 died", gettime() - table->start_simulation);
	pthread_mutex_unlock(&table->write_mutex);
}

static void	*dinner(void *data)
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
		if (get_bool(&philo->philo_mutex, &philo->full))
			break ;
	}
	return (NULL);
}

static void	simulation_start(t_table *table)
{
	int	i;

	i = -1;
	if (table->meals_limit == 0)
		return ;
	else if (table->philo_nbr == 1)
	{
		lonely_simulation(table);
		clean(&table);
		return ;
	}
	else
		while (++i < table->philo_nbr)
			thread_create(&table->philos[i].thread_id, &dinner,
				&table->philos[i]);
	thread_create(&table->monitor_thread, &monitor_function, table);
	table->start_simulation = gettime();
	i = -1;
	set_bool(&table->table_mutex, &table->all_threads_ready, true);
	pthread_join(table->monitor_thread, NULL);
	while (++i < table->philo_nbr)
		pthread_join(table->philos[i].thread_id, NULL);
	set_bool(&table->table_mutex, &table->end_simulation, true);
	clean(&table);
}

int	main(int ac, char **av)
{
	t_table	table;

	if (ac != 5 && ac != 6)
		simulation_error("Wrong input! Try:\n./philo 5 400 150 150");
	parse_input(&table, av);
	data_init(&table);
	simulation_start(&table);
	return (0);
}
