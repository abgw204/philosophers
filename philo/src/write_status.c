/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_status.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gada-sil <gada-sil@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 18:00:16 by gada-sil          #+#    #+#             */
/*   Updated: 2025/04/09 18:00:17 by gada-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	write_status(t_philo_sts status, t_philo *philo)
{
	long	elapsed;

	elapsed = gettime() - philo->table->start_simulation;
	pthread_mutex_lock(&philo->table->write_mutex);
	if (get_bool(&philo->philo_mutex, &philo->table->end_simulation))
	{
		pthread_mutex_unlock(&philo->table->write_mutex);
		return ;
	}
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
	pthread_mutex_unlock(&philo->table->write_mutex);
}
