/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_list_util.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfuhlenb <vfuhlenb@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 16:14:40 by vfuhlenb          #+#    #+#             */
/*   Updated: 2022/10/26 17:21:51 by vfuhlenb         ###   ########.fr       */
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
int	countLinkedList(t_linkedList *list)
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

// prints the list
void	displayLinkedList(t_linkedList *list)
{
	t_node *current;

	current = list->head;
	while (current != NULL)
	{
		printf("%s$\n", current->data); // DEBUG remove $ for production
		current = current->next;
	}
}

// void	clearLinkedList(t_linkedList **lst, void (*del)(void*))
// {
// 	t_list	*temp;

// 	if (!lst && !del)
// 		return ;
// 	while (*lst)
// 	{
// 		temp = (*lst)->next;
// 		del((*lst)->content);
// 		free(*lst);
// 		*lst = temp;
// 	}
// 	*lst = NULL;
// }
