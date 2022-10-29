/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_sh_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dimbrea <dimbrea@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 16:14:40 by vfuhlenb          #+#    #+#             */
/*   Updated: 2022/10/27 10:55:47 by dimbrea          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

// initializes the list
void	initializeList(t_linkedList *list)
{
	list->head = NULL;
	list->tail = NULL;
	list->current = NULL;
}

// adds a node at the top
void	addHead(t_linkedList *list, void *data)
{
	t_node *node;

	node = (t_node *) malloc(sizeof(t_node));
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
void	addTail(t_linkedList *list, void *data)
{
	t_node *node;

	node = (t_node *) malloc(sizeof(t_node));
	node->data = data;
	node->next = NULL;
	if (list->head == NULL)
		list->head = node;
	else
		list->tail->next = node;
	list->tail = node;
}

// prints the list
void	displayLinkedList(t_linkedList *list)
{
	t_node *current;

	current = list->head;
	while (current != NULL)
	{
		printf("%p\n", current->data);
		current = current->next;
	}
}
