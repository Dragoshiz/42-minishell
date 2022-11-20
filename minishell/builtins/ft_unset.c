/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfuhlenb <vfuhlenb@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 14:50:57 by dimbrea           #+#    #+#             */
/*   Updated: 2022/11/20 01:37:11 by vfuhlenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	unset_exp(t_iovars *iov, t_token *curr, size_t len);
static int	hv_exp_next(t_iovars *iov, t_node *exp);

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

static int	hv_exp_next(t_iovars *iov, t_node *exp)
{
	if (!iov->vars->exp_lst->head->next)
	{
		free(iov->vars->exp_lst->head->data); // DEBUG 20.11. 01:30
		free(iov->vars->exp_lst->head);
		iov->vars->exp_lst->head = NULL;
		return (0);
	}
	iov->vars->exp_lst->head = iov->vars->exp_lst->head->next;
	free_node(exp);
	exp = iov->vars->exp_lst->head;
	return (1);
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
		if (!hv_exp_next(iov, exp))
			return ;
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

void	free_node(t_node *node)
{
	free(node->data);
	free(node);
}
