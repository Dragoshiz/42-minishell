/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dimbrea <dimbrea@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 17:46:53 by vfuhlenb          #+#    #+#             */
/*   Updated: 2022/11/07 20:10:07 by dimbrea          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_ordered(t_linked_list *exp_lst)
{
	t_node	*current;
	int		i;

	i = 0;
	current = exp_lst->head;
	while (current->next != NULL)
	{
		if (ft_strncmp(current->data, current->next->data, 5) > 0)
			return (1);
		current = current->next;
	}
	return (0);
}

//remember to FREE EXP_LST
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

int	ft_update_data(t_vars *vars, char	*data)
{
	t_node	*curr;
	int		len;

	len = 0;
	while (data[len] != '=' && data[len])
		len++;
	curr = vars->env_list->head;
	while (curr != NULL)
	{
		if (ft_strncmp(curr->data, data, len) == 0)
		{
			free(curr->data);
			curr->data = ft_strdup(data);
			ft_update_data(vars, data);
			return (1);
		}
		curr = curr->next;
	}
	return (0);
}

int	ft_update_exp(t_linked_list *exp_lst, char *data)
{
	t_node	*curr;
	int		len;
	int		len2;

	len = 0;
	len2 = 0;
	while (data[len] != '=' && data[len])
		len++;
	curr = exp_lst->head;
	while (curr != NULL)
	{
		while (*(char*)curr->next->data[len2++] != '=' && curr->next->data[len2])//from here have to find solution to have both the same lenght till = sign
		if (ft_strncmp(curr->data, data, len) == 0)
		{
			if (len >= len2)
			{
				free(curr->data);
				curr->data = ft_strdup(data);
				return (1);
			}
		}
		curr = curr->next;
	}
	return (0);
}

void	ft_printnsortexp(t_linked_list *exp_lst)
{
	t_node	*current;
	char	*tmp;

	current = exp_lst->head;
	while (is_ordered(exp_lst) == 1)
	{
		if (current->next == NULL)
			current = exp_lst->head;
		if (ft_strncmp(current->data, current->next->data, 5) > 0)
		{
			tmp = current->data;
			current->data = current->next->data;
			current->next->data = tmp;
		}
		current = current->next;
	}
	current = exp_lst->head;
	while (current != NULL)
	{
		printf("declare -x %s\n", current->data);
		current = current->next;
	}
}

void	ft_add2env(t_vars *vars, char *data)
{
	char	*i;

	i = ft_strchr(data, '=');
	if (i && *i == '=' && i-- != NULL)
	{
		if (ft_update_data(vars, data) == 1)
		{
			ft_update_exp(vars->exp_lst, data);
			return ;
		}
		add_tail(vars->env_list, data);
	}
}

void	ft_get_var(t_vars *vars)
{
	t_token	*curr;
	t_token	*previous;
	int		pipe_nr;

	curr = vars->parse->token_list->head;
	while (curr != NULL)
	{
		if (ft_strncmp(curr->data, "export", 6) == 0)
		{
			pipe_nr = curr->pipe_nbr;
			while (pipe_nr == curr->pipe_nbr && curr->next != NULL)
			{
				previous = curr;
				curr = curr->next;
				if (ft_update_exp(vars->exp_lst, curr->data) != 1)
				{
					ft_add2env(vars, curr->data);
					add_tail(vars->exp_lst, curr->data);
				}
			}
			curr = curr->next;
		}
	}
}

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
			return ;
		}
	}
	ft_get_var(vars);
}