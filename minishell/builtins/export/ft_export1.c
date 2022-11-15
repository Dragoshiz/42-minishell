/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dimbrea <dimbrea@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 14:32:17 by dimbrea           #+#    #+#             */
/*   Updated: 2022/11/15 11:16:15 by dimbrea          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

//checks if exp_lst is sorted
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

//updates the export lst
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
