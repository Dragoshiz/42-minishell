/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dimbrea <dimbrea@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 14:29:42 by dimbrea           #+#    #+#             */
/*   Updated: 2022/11/08 15:15:07 by dimbrea          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

//sorts and prints export
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

//adds variable to env only if valid
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
		add_tail(vars->env_list, ft_strdup(data));
	}
}

//check if curr->data has an equal sign
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

//checks if variable is a valid identifier
int	ft_is_valid(t_token *curr, char *curr_data)
{
	if (ft_isalpha(curr_data[0]) == 0)
	{
		printf("minishell: export: '%s': not a valid identifier\n", curr_data);
		curr = curr->next;
		g_exit = 1;
		return (1);
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
			curr = curr->next;
		}
	}
}
