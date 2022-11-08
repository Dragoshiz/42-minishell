/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfuhlenb <vfuhlenb@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 17:46:53 by vfuhlenb          #+#    #+#             */
/*   Updated: 2022/11/08 12:32:18 by vfuhlenb         ###   ########.fr       */
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

int	ft_hv_equal(char *curr_data)
{
	int	i;

	i = 0;
	while (curr_data[i])
	{
		if (curr_data[i] == '=')
			return (1);
		i++;
	}
	return (0);
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
			if ((data[len] == '=' && ft_hv_equal(curr->data) == 1)
				|| (data[len] == '=' && ft_hv_equal(curr->data) == 0))
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


int	ft_update_exp(t_linked_list *exp_lst, char *data)
{
	t_node	*curr;
	int		len;

	len = 0;
	while (data[len] != '=' && data[len])
		len++;
	curr = exp_lst->head;
	while (curr != NULL)
	{
		if (ft_strncmp(curr->data, data, len) == 0)
		{
			if ((data[len] == '=' && ft_hv_equal(curr->data) == 1)
				|| (data[len] == '=' && ft_hv_equal(curr->data) == 0))
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
		printf("%c", *i);
		if (ft_update_data(vars, data) == 1)
		{
			ft_update_exp(vars->exp_lst, data);
			return ;
		}
		add_tail(vars->env_list, data);
	}
}

int	ft_chk_cur_env(t_linked_list *exp_lst, char *data)
{
	t_node	*curr;
	int		len;

	len = 0;
	while (data[len] != '=' && data[len])
		len++;
	curr = exp_lst->head;
	while (curr != NULL)
	{
		if (strncmp(curr->data, data, len) == 0)
		{
			if (data[len] != '=')
				return (1);
		}
		curr = curr->next;
	}
	return (0);
}

void	ft_is_valid(t_token *curr, char *curr_data)
{
	if (ft_isalpha(curr_data[0]) == 0)
	{
		printf("minishell: export: '%s': not a valid identifier\n", curr_data);
		curr = curr->next;
	}
}

void	ft_get_var(t_vars *vars)
{
	t_token	*curr;
	int		pipe_nr;

	curr = vars->parse->token_list->head;
	while (curr != NULL)
	{
		if (ft_strncmp(curr->data, "export", 6) == 0)
		{
			pipe_nr = curr->pipe_nbr;
			while (pipe_nr == curr->pipe_nbr && curr->next != NULL)
			{
				curr = curr->next;
				ft_is_valid(curr, curr->data);
				if (ft_update_exp(vars->exp_lst, curr->data) != 1)
				{
					if (ft_chk_cur_env(vars->exp_lst, curr->data) == 0)
						add_tail(vars->exp_lst, curr->data);
				}
				ft_add2env(vars, curr->data);
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