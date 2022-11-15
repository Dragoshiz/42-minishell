/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfuhlenb <vfuhlenb@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 14:50:57 by dimbrea           #+#    #+#             */
/*   Updated: 2022/11/15 15:41:06 by vfuhlenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	unset_exp(t_iovars *iov, t_token *curr, size_t len);
static void	unset_env(t_iovars *iov, t_token *curr, size_t len);
static void	free_node(t_node *node);

void	ft_unset(t_token *current, t_iovars *iov, int pipe_num)
{
	t_token	*curr;
	size_t	len;

	len = 0;
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
			{
				unset_exp(iov, curr->next, len);
				unset_env(iov, curr->next, len);
			}
			curr = curr->next;
		}
	}
	update_env_sh(iov->vars);
}

static void	unset_env(t_iovars *iov, t_token *curr, size_t len)
{
	t_node	*env;
	t_node	*tmp;

	len = ft_strlen(curr->data);
	env = iov->vars->env_list->head;
	if (ft_strncmp(env->data, curr->data, len) == 0 \
		&& env->data[len] == '=')
	{
		iov->vars->env_list->head = iov->vars->env_list->head->next;
		free_node(env);
		env = iov->vars->env_list->head;
	}
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
		if (env->next)
			env = env->next;
	}
}

static void	unset_exp(t_iovars *iov, t_token *curr, size_t len)
{
	t_node	*exp;
	t_node	*tmp;

	len = ft_strlen(curr->data);
	exp = iov->vars->exp_lst->head;
	if (ft_strncmp(exp->data, curr->data, len) == 0 && \
	(exp->data[len] == '=' || ft_strlen(exp->data) == len))
	{
		iov->vars->exp_lst->head = iov->vars->exp_lst->head->next;
		free_node(exp);
		exp = iov->vars->exp_lst->head;
	}
	while (exp->next)
	{
		if (ft_strncmp(exp->next->data, curr->data, len) == 0 && \
		(exp->next->data[len] == '=' || ft_strlen(exp->next->data) == len))
		{
			tmp = exp->next;
			if (exp->next)
				exp->next = exp->next->next;
			free_node(tmp);
		}
		if (exp->next)
			exp = exp->next;
	}
}

static void	free_node(t_node *node)
{
	free(node->data);
	free(node);
}
