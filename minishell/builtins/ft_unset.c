/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfuhlenb <vfuhlenb@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 14:50:57 by dimbrea           #+#    #+#             */
/*   Updated: 2022/11/14 11:37:49 by vfuhlenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_is_equal(char *env_data, char *data)
{
	size_t	i;

	i = 0;
	while (env_data[i] != '=' && env_data[i])
		i++;
	if (ft_strlen(data) == i)
		return (1);
	return (0);
}

int	ft_chk_equal(char *data)
{
	while (*data)
	{
		if (*data == '=')
			return (1);
		data++;
	}
	return (0);
}

void	ft_search_env_lst(t_token *next, t_vars *vars)
{
	t_node	*env;
	t_node	*tmp;
	t_token	*token;

	token = next;
	while (token != NULL)
	{
		env = vars->env_list->head;
		while (env->next != NULL)
		{
			if (ft_chk_equal(token->data) == 1)
			{
				printf("minishell: unset: `%s': not a valid identifier\n", token->data);
				if (token->next != NULL)
					token = token->next;
				else
					return ;
			}
			if (ft_strncmp(env->next->data, token->data,
					ft_strlen(token->data)) == 0 && ft_is_equal \
					(env->next->data, token->data) == 1)
			{
				tmp = env->next;
				if (env->next->next != NULL)
				{
					env->next = env->next->next;
					printf("%s\n", env->next->data);
				}
				free(tmp->data);
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
			ft_putstr_fd("unset: not enough arguments\n", 1);
			g_exit = 0;
			return ;
		}
		if (curr->next != NULL && curr->next->pipe_nbr == pipe_nr)
		{
			ft_search_env_lst(curr->next, vars);
		}
	}
}
