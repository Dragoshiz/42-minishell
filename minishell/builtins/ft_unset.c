/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfuhlenb <vfuhlenb@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 14:50:57 by dimbrea           #+#    #+#             */
/*   Updated: 2022/11/15 12:44:19 by vfuhlenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	unset_env(t_iovars *iov, t_token *curr)
{
	t_node	*env;
	// t_node	*tmp;

	env = iov->vars->env_list->head;
	if (ft_strncmp(env->data, curr->data, ft_strlen(curr->data)) == 0)
	{
		free(env->data);
		free(env);
		iov->vars->env_list->head = iov->vars->env_list->head->next;
		env = iov->vars->env_list->head;
	}
	while (env->next)
	{
		
	}
	update_env_sh(iov->vars);
}

static void	unset_var(t_iovars *iov, t_token *curr)
{
	unset_env(iov, curr);
	// unset_exp(iov, curr);
}

void	ft_unset(t_token *current, t_iovars *iov, int pipe_num)
{
	t_token	*curr;

	curr = current;
	if (curr->next == NULL || (curr->next && curr->pipe_nbr != pipe_num))
	{
		ft_putstr_fd("unset: not enough arguments\n", 1);
		g_exit = 0;
		return ;
	}
	else if (curr->next && curr->pipe_nbr == pipe_num)
	{
		while (curr->next && curr->pipe_nbr == pipe_num)
		{
			if (curr->next->type == 0 && \
			is_variable_str(curr->next->data))
				unset_var(iov, curr->next);
			// else
			// 	printf("%s is not a valid variable string\n", curr->next->data);
			curr = curr->next;
		}
	}
}
