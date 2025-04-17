/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gada-sil <gada-sil@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 18:00:28 by gada-sil          #+#    #+#             */
/*   Updated: 2025/04/09 18:00:29 by gada-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

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

void	philo_dead(t_philo *philo)
{
	long long elapsed;

	elapsed = gettime() - philo->table->start_simulation;
	set_bool(&philo->table->table_mutex, &philo->table->end_simulation, true);	
	printf("%-6lld %d ", elapsed, philo->id);
	printf("is dead\n");
}