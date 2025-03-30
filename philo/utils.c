/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gada-sil <gada-sil@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/06 15:43:49 by gada-sil          #+#    #+#             */
/*   Updated: 2024/10/06 15:43:50 by gada-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	simulation_error(char *error_message)
{
	printf("%s", error_message);
	exit(1);
}

void	*safe_malloc(size_t bytes)
{
	void	*ptr;

	ptr = malloc(bytes);
	if (!ptr)
		simulation_error("Malloc error!(something is very wrong)\n");
	return (ptr);
}

void	wait_all_threads(t_table *table)
{
	while (!get_bool(&table->table_mutex, &table->all_threads_ready))
		usleep(1);
}

bool	all_threads_running(pthread_mutex_t *mutex, long *threads, long philo_nbr)
{
	bool	ret;

	ret = false;
	pthread_mutex_lock(mutex);
	if (*threads == philo_nbr)
		ret = true;
	pthread_mutex_unlock(mutex);
	return (ret);
}

void	increment_long(pthread_mutex_t *mutex, long *value)
{
	pthread_mutex_lock(mutex);
	(*value)++;
	pthread_mutex_unlock(mutex);
}