/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   isleep.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gada-sil <gada-sil@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 18:00:12 by gada-sil          #+#    #+#             */
/*   Updated: 2025/04/09 18:00:13 by gada-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	isleep(long time)
{
	long	start;

	time = time / 1e3;
	start = gettime() + time;
	while (gettime() < start)
		usleep(1);
}
