/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfuhlenb <vfuhlenb@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 18:43:34 by vfuhlenb          #+#    #+#             */
/*   Updated: 2022/11/18 18:48:30 by vfuhlenb         ###   ########.fr       */
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
		}
		if (!env->next)
			break ;
		env = env->next;
	}
}
