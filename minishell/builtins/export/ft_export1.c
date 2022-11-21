/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dimbrea <dimbrea@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 14:32:17 by dimbrea           #+#    #+#             */
/*   Updated: 2022/11/21 15:07:13 by dimbrea          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

//checks if exp_lst is sorted
int	is_ordered(t_linked_list *exp_lst)
{
	t_node	*current;

	current = exp_lst->head;
	if (current == NULL)
		return (0);
	while (current->next != NULL)
	{
		if (ft_strncmp(current->data, current->next->data, 5) > 0)
			return (1);
		current = current->next;
	}
	return (0);
}

//self explanatory
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

//updates the env_lst
int	ft_update_data(t_vars *vars, char	*data)
{
	t_node	*curr;
	int		len;
	int		i;

	len = 0;
	while (data[len] != '=' && data[len])
		len++;
	curr = vars->env_list->head;
	while (curr != NULL)
	{
		if (ft_strncmp(curr->data, data, len) == 0)
		{
			i = 0;
			while (curr->data[i] != '=' && curr->data[i])
				i++;
			if (len == i && data[len] == '=')
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

//updates the export lst
int	ft_update_exp(t_linked_list *exp_lst, char *data)
{
	t_node	*curr;
	int		len;
	int		i;

	len = 0;
	while (data[len] != '=' && data[len])
		len++;
	curr = exp_lst->head;
	while (curr != NULL)
	{
		if (ft_strncmp(curr->data, data, len) == 0)
		{
			i = 0;
			while (curr->data[i] != '=' && curr->data[i])
				i++;
			if (len == i && data[len] == '=')
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

//puts variables used after export in exp_lst and
// if they are valid also in env_lst
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
				if (ft_is_valid(curr, curr->data) == 0)
				{
					if (ft_update_exp(vars->exp_lst, curr->data) != 1)
					{
						if (ft_chk_cur_env(vars->exp_lst, curr->data) == 0)
							add_tail(vars->exp_lst, ft_strdup(curr->data));
					}
					ft_add2env(vars, curr->data);
				}
			}
		}
		curr = curr->next;
	}
}
