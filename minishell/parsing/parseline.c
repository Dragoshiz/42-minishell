/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parseline.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfuhlenb <vfuhlenb@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 12:40:48 by vfuhlenb          #+#    #+#             */
/*   Updated: 2022/10/18 11:35:48 by vfuhlenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// # of ENV Elements
// create Link List for ENV
// Strdup for each element

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
		printf("%s\n", current->data);
		current = current->next;
	}
}

// initializes the list
void	initializeList(t_linkedList *list)
{
	list->head = NULL;
	list->tail = NULL;
	list->current = NULL;
}

// initializes ENV_SH_LIST
void	initialize_env_sh_list(t_vars *vars, char *env[])
{
	int	i;

	// check if env is valid and has content
	initializeList(&vars->env_sh_list);
	i = 0;
	while (env[i])
	{
		addTail(&vars->env_sh_list, env[i]);
		i++;
	}
	vars->num_env_sh = i;
}

// first pass: check for pipes -> quotes

// second pass: expansion of variables

// third pass: extract tokens

// extract tokens from the line
void	get_tokens(t_vars *vars)
{
//	printf("Line: %s\n", vars->line);
}