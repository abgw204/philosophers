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

void	simulation_error(int error)
{
	if (1 == error)
	{
		printf(BOLD_RED "Wrong input! Try the following example:\n" RESET);
		printf("./philo 5 200 500 300 [5]");
	}
	else if (2 == error)
		printf("ERROR");
	exit(1);
}

void	*safe_malloc(size_t bytes)
{
	void	*ptr;

	ptr = malloc(bytes);
	if (!ptr)
		simulation_error(2);
	return (ptr);
}

void	wait_all_threads(t_table *table)
{
	while (!get_bool(&table->table_mutex, &table->all_threads_ready))
		;
}
