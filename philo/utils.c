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

void	appendPhilo(t_philo **philo, t_philo *new)
{
	t_philo	*current;

	if (philo == NULL || new == NULL)
		return ;
	if (*philo == NULL)
	{
		*philo = new;
		return ;
	}
	current = *philo;
	while (current->next != NULL)
		current = current->next;
	current->next = new;
	new->prev = current;
}

t_philo	*newPhilo(int philoId)
{
	t_philo	*new_node;

	new_node = (t_philo *)malloc(sizeof(t_philo));
	if (!new_node)
		return (NULL);
	new_node->philoId = philoId;
	new_node->next = NULL;
	new_node->prev = NULL;
	return (new_node);
}

int	list_size(t_philo *lst)
{
	size_t	i;
	t_philo	*temp;

	i = 0;
	if (lst == NULL)
		return (0);
	temp = lst;
	while (temp)
	{
		i++;
		temp = temp->next;
	}
	return (i);
}

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
