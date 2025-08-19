/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gettime.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gada-sil <gada-sil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 18:00:06 by gada-sil          #+#    #+#             */
/*   Updated: 2025/05/13 14:37:46 by gada-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

long	gettime(void)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL))
		simulation_error("Function gettimeofday failed\n");
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}
