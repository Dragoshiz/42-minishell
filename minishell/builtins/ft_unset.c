/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dimbrea <dimbrea@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 14:50:57 by dimbrea           #+#    #+#             */
/*   Updated: 2022/11/08 16:33:38 by dimbrea          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int
void	ft_search_env_lst(t_token *curr, t_vars *vars)
{
	t_node	*env;
	t_node	*tmp;
	t_token	*token;

	token = curr;
	while (token != NULL)
	{
		env = vars->env_list->head;
		while (env->next != NULL)
		{
			if (ft_strncmp(env->next->data, token->data, ft_strlen(token->data)) == 0)
			{
				printf("%s\n", env->data);
				tmp = env->next;
				env->next = env->next->next;
				free(tmp);
				break ;
			}
			env = env->next;
		}
		token = token->next;
	}
}

void	ft_unset(t_vars *vars)
{
	t_token	*curr;
	int		pipe_nr;

	curr = vars->parse->token_list->head;
	pipe_nr = curr->pipe_nbr;
	if (ft_strncmp(curr->data, "unset", 5) == 0)
	{
		if (curr->next == NULL)
		{
			printf("unset: not enough arguments\n");
			g_exit = 1;
			return ;
		}
		if (curr->next != NULL && curr->next->pipe_nbr == pipe_nr)
		{
			ft_search_env_lst(curr, vars);
		}
	}
}
