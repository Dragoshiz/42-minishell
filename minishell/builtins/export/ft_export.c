/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dimbrea <dimbrea@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 17:46:53 by vfuhlenb          #+#    #+#             */
/*   Updated: 2022/11/18 14:02:48 by dimbrea          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

//remember to FREE EXP_LST
//copies env_lst to export list
void	ft_get_export(t_iovars *iov)
{
	t_node	*current;
	int		i;

	i = 0;
	current = iov->vars->env_list->head;
	iov->vars->exp_lst = ft_calloc(1, sizeof(t_linked_list));
	initialize_list(iov->vars->exp_lst);
	while (current != NULL)
	{
		if (ft_strncmp(current->data, "OLDPWD=", ft_strlen("OLDPWD=")) == 0)
			i++;
		add_tail(iov->vars->exp_lst, ft_strdup(current->data));
		current = current->next;
	}
	if (i == 0)
		add_tail(iov->vars->exp_lst, ft_strdup("OLDPWD"));
}

//check if export is the single command if not goes to ft_getvar
void	ft_export(t_iovars *iov, int num_pipe)
{
	t_token	*curr;
	int		pipe_nr;

	curr = iov->vars->parse->token_list->head;
	while (curr && curr->pipe_nbr != num_pipe)
		curr = curr->next;
	pipe_nr = curr->pipe_nbr;
	if (ft_strncmp(curr->data, "export", 6) == 0)
	{
		if ((curr->next != NULL && curr->next->pipe_nbr != pipe_nr)
			|| curr->next == NULL)
		{
			ft_printnsortexp(iov, iov->vars->exp_lst, num_pipe);
			g_exit = 0;
			return ;
		}
	}
	ft_get_var(iov->vars);
	g_exit = 0;
}
