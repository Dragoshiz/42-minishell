/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_list_util.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfuhlenb <vfuhlenb@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 16:14:40 by vfuhlenb          #+#    #+#             */
/*   Updated: 2022/11/02 20:57:57 by vfuhlenb         ###   ########.fr       */
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

	node = calloc(1, sizeof(t_node));
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

	node = calloc(1, sizeof(t_node));
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

// DEBUG prints the list
void	display_linked_list(t_linked_list *list)
{
	t_node	*current;

	current = list->head;
	while (current != NULL)
	{
		printf("%s\n", current->data); // DEBUG remove $ for production
		current = current->next;
	}
}

void	delete_list(t_linked_list *list)
{
	t_node	*temp;

	if (list->current == list->head)
	{
		if (list->head->next == NULL)
			list->head = list->tail = NULL;
		else
			list->head = list->head->next;
	}
	else
	{
		temp = list->head;
		while (temp != NULL && temp->next != list->current)
		{
			free (temp->data);
			temp = temp->next;
		}
		if (temp != NULL)
			temp->next = list->current->next;
	}
	free(list->current);
	if (list)
		free(list);
}
