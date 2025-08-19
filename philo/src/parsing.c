/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gada-sil <gada-sil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 18:00:40 by gada-sil          #+#    #+#             */
/*   Updated: 2025/05/13 14:46:40 by gada-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

static int	ft_isdigit(int c)
{
	return (c >= '0' && c <= '9');
}

static int	atoi2(const char *str)
{
	long	res;
	int		sign;

	res = 0;
	sign = 1;
	while (*str == ' ' || (*str >= 9 && *str <= 13))
		str++;
	if (!(*str >= '0' && *str <= '9'))
	{
		if (*str == '-')
			sign = -1;
		else if (*str != '+')
			simulation_error("Invalid character!\n");
		str++;
	}
	while (*str)
	{
		if (!ft_isdigit(*str))
			simulation_error("Invalid character!\n");
		res = res * 10 + (*str++ - 48);
	}
	if ((res * sign) > 2147483647 || (res * sign) < 0)
		simulation_error("Negative or greater than int max!\n");
	return (res * sign);
}

void	parse_input(t_table *table, char **av)
{
	table->philo_nbr = atoi2(av[1]);
	table->time_to_die = atoi2(av[2]);
	table->time_to_eat = atoi2(av[3]) * 1e3;
	table->time_to_sleep = atoi2(av[4]) * 1e3;
	if (av[5])
		table->meals_limit = atoi2(av[5]);
	else
		table->meals_limit = -1;
}
