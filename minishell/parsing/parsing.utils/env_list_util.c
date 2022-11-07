/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_list_util.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfuhlenb <vfuhlenb@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 16:14:40 by vfuhlenb          #+#    #+#             */
/*   Updated: 2022/11/07 17:53:33 by vfuhlenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

// initializes the list
void	initialize_list(t_linked_list *list)
{
	list->head = NULL;
	list->tail = NULL;
	list->current = NULL;
}

// adds a node at the top
void	add_head(t_linked_list *list, void *data)
{
	t_node	*node;

	node = ft_calloc(1, sizeof(t_node));
	node->data = data;
	if (list->head == NULL)
	{
		list->tail = node;
		node->next = NULL;
	}
	else
		node->next = list->head;
	list->head = node;
}

// adds a node at the tail
void	add_tail(t_linked_list *list, void *data)
{
	t_node	*node;

	node = ft_calloc(1, sizeof(t_node));
	node->data = data;
	node->next = NULL;
	if (list->head == NULL)
		list->head = node;
	else
		list->tail->next = node;
	list->tail = node;
}

// prints the list
int	count_linked_list(t_linked_list *list)
{
	int		i;
	t_node	*current;

	current = list->head;
	i = 0;
	while (current != NULL)
	{
		i++;
		current = current->next;
	}
	return (i);
}

void	delete_list(t_linked_list *list)
{
	t_node	*temp;

	while (list->head != NULL)
	{
		temp = list->head;
		list->head = list->head->next;
		free(temp->data);
		free(temp);
	}
}
