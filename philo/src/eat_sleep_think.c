/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat_sleep_think.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gada-sil <gada-sil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 17:59:51 by gada-sil          #+#    #+#             */
/*   Updated: 2025/05/21 22:08:40 by gada-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->first_fork->fork);
	if (get_bool(&philo->table->table_mutex, &philo->table->end_simulation))
	{
		pthread_mutex_unlock(&philo->first_fork->fork);
		return ;
	}
	write_status(TAKE_FIRST_FORK, philo);
	pthread_mutex_lock(&philo->second_fork->fork);
	if (get_bool(&philo->table->table_mutex, &philo->table->end_simulation))
	{
		pthread_mutex_unlock(&philo->first_fork->fork);
		pthread_mutex_unlock(&philo->second_fork->fork);
		return ;
	}
	write_status(TAKE_SECOND_FORK, philo);
	set_long(&philo->philo_mutex, &philo->last_meal_time, gettime());
	write_status(EATING, philo);
	increment_long(&philo->philo_mutex, &philo->meals_counter);
	if (get_long(&philo->table->table_mutex, &philo->meals_counter)
		== philo->table->meals_limit)
		set_bool(&philo->philo_mutex, &philo->full, true);
	isleep(philo->table->time_to_eat);
	pthread_mutex_unlock(&philo->first_fork->fork);
	pthread_mutex_unlock(&philo->second_fork->fork);
}

void	sleeping(t_philo *philo)
{
	write_status(SLEEPING, philo);
	isleep(philo->table->time_to_sleep);
}

void	thinking(t_philo *philo)
{
	write_status(THINKING, philo);
	usleep(20);
}
