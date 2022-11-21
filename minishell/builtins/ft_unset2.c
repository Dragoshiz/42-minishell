/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfuhlenb <vfuhlenb@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 18:43:34 by vfuhlenb          #+#    #+#             */
/*   Updated: 2022/11/21 17:38:57 by vfuhlenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	init_unset_env(t_iovars *iov, t_token *curr, size_t len, \
	t_node *env)
{
	if (ft_strncmp(env->data, curr->data, len) == 0 \
		&& env->data[len] == '=')
	{
		iov->vars->env_list->head = iov->vars->env_list->head->next;
		free_node(env);
		env = iov->vars->env_list->head;
	}
}

void	unset_env(t_iovars *iov, t_token *curr, size_t len)
{
	t_node	*env;
	t_node	*tmp;

	len = ft_strlen(curr->data);
	env = iov->vars->env_list->head;
	if (!env)
		return ;
	init_unset_env(iov, curr, len, env);
	if (!env)
		return ;
	while (env->next)
	{
		if (ft_strncmp(env->next->data, curr->data, len) == 0 \
			&& env->next->data[len] == '=')
		{
			tmp = env->next;
			if (env->next)
				env->next = env->next->next;
			free_node(tmp);
			ft_replace_tail(iov->vars->env_list);
		}
		if (!env->next)
			break ;
		env = env->next;
	}
}

//checks if variable is a valid identifier
int	ft_is_valid_unset(t_token *curr, char *curr_data)
{
	int	valid;
	int	i;

	i = 0;
	valid = 0;
	while (curr_data[i])
	{
		if (is_variable_char(curr_data[i]) == 0 || \
		is_variable_start_char(curr_data[0]) == 0)
			valid = 1;
		i++;
	}
	if (valid == 1)
	{
		ft_putstr_fd("minishell: unset: ", STDERR_FILENO);
		ft_putstr_fd(curr_data, STDERR_FILENO);
		ft_putstr_fd(": not a valid identifier\n", STDERR_FILENO);
		curr = curr->next;
		g_exit = 1;
		return (valid);
	}
	return (valid);
}
