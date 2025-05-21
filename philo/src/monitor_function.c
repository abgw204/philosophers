/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_function.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gada-sil <gada-sil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 18:00:50 by gada-sil          #+#    #+#             */
/*   Updated: 2025/04/18 05:45:01 by gada-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	*monitor_function(void *data)
{
	t_table	*table;
	int		i;

	table = (t_table *)data;
	while (!all_threads_running(&table->table_mutex, &table->threads_running,
			table->philo_nbr))
    usleep(1);
	while (!simulation_finished(table))
	{
		i = -1;
		while (++i < table->philo_nbr && !simulation_finished(table))
		{
			if (is_philo_gone(table->philos + i))
			{
				philo_dead(table->philos + i);
				return (NULL);
			}
		}
		if (everyone_is_full(table))
			return (NULL);
		usleep(1);
	}
	return (NULL);
}
