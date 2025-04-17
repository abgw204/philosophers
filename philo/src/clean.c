/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gada-sil <gada-sil@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 17:59:47 by gada-sil          #+#    #+#             */
/*   Updated: 2025/04/09 17:59:48 by gada-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	clean_philo(t_table **table)
{
	int	i;

	i = -1;
	while (++i < (*table)->philo_nbr)
		pthread_mutex_destroy(&(*table)->philos[i].philo_mutex);
	free((*table)->philos);
	free((*table)->forks);
}

void	clean(t_table **table)
{
	int	i;

	i = -1;
	while (++i < (*table)->philo_nbr)
		pthread_mutex_destroy(&(*table)->forks[i].fork);
	pthread_mutex_destroy(&(*table)->write_mutex);
	pthread_mutex_destroy(&(*table)->table_mutex);
	clean_philo(table);
}
