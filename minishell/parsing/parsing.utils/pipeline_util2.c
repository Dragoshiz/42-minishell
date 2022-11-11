/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline_util2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfuhlenb <vfuhlenb@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 15:56:56 by vfuhlenb          #+#    #+#             */
/*   Updated: 2022/11/11 09:46:01 by vfuhlenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

// adds a node at the tail
void	add_tail_pipe(t_parsing *parsing, void *data)
{
	t_node	*node;

	node = ft_calloc(1, sizeof(t_node));
	node->data = data;
	node->next = NULL;
	if (parsing->pipeline->head == NULL)
		parsing->pipeline->head = node;
	else
		parsing->pipeline->tail->next = node;
	parsing->pipeline->tail = node;
	if (!is_whitespace(data))
		parsing->num_cmds++;
}
