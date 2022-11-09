/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dimbrea <dimbrea@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 17:46:53 by vfuhlenb          #+#    #+#             */
/*   Updated: 2022/11/09 10:28:59 by dimbrea          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

//remember to FREE EXP_LST
//copies env_lst to export list
void	ft_get_export(t_vars *vars)
{
	t_node			*current;

	current = vars->env_list->head;
	vars->exp_lst = ft_calloc(1, sizeof(t_linked_list));
	initialize_list(vars->exp_lst);
	while (current != NULL)
	{
		add_tail(vars->exp_lst, ft_strdup(current->data));
		current = current->next;
	}
}

//check if export is the single command if not goes to ft_getvar
void	ft_export(t_vars *vars)
{
	t_token	*curr;
	int		pipe_nr;

	curr = vars->parse->token_list->head;
	pipe_nr = curr->pipe_nbr;
	if (ft_strncmp(curr->data, "export", 6) == 0)
	{
		if ((curr->next != NULL && curr->next->pipe_nbr != pipe_nr)
			|| curr->next == NULL)
		{
			ft_printnsortexp(vars->exp_lst);
			g_exit = 0;
			return ;
		}
	}
	ft_get_var(vars);
	g_exit = 0;
}
