/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline_util.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfuhlenb <vfuhlenb@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 15:56:56 by vfuhlenb          #+#    #+#             */
/*   Updated: 2022/10/28 11:37:52 by vfuhlenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

// transfers strings from linked list to arg array
void	fill_args(t_parsing *parsing)
{
	int	i;

	parsing->pipeline->current = parsing->pipeline->head;
	parsing->s_vars->num_args = countLinkedList(parsing->pipeline);
	parsing->s_vars->args = malloc(sizeof(char *) * parsing->s_vars->num_args);
	i = 0;
	while (i < parsing->s_vars->num_args)
	{
		parsing->s_vars->args[i] = ft_strdup(parsing->pipeline->current->data);
		if (parsing->pipeline->current->next)
			parsing->pipeline->current = parsing->pipeline->current->next;
		i++;
	}
}
