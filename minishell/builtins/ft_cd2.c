/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dimbrea <dimbrea@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 14:55:15 by dimbrea           #+#    #+#             */
/*   Updated: 2022/11/18 16:44:20 by dimbrea          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	*pwd_data(t_linked_list *list, char *str)
{
	t_node	*curr;
	char	*p;

	curr = list->head;
	p = NULL;
	while (curr)
	{
		if (ft_strncmp(curr->data, str, ft_strlen(str)) == 0)
		{
			p = ft_strdup(curr->data);
			return (p);
		}
		curr = curr->next;
	}
	return (p);
}

// static update_pwd2(t_vars *vars, char *cwd, char *pwd, char *oldpwd)
// {
	
// }


void	update_pwd(t_vars *vars, char *cwd, char *pwd, char *oldpwd)
{
	char	*data;
	char	*old_data;

	if (find_var(vars->env_list, pwd))
	{
		data = pwd_data(vars->env_list, pwd);
		if (!find_var(vars->env_list, oldpwd))
			add_tail(vars->env_list, ft_strdup(data));
		else
		{
			old_data = pwd_data(vars->env_list, oldpwd);
			free (old_data);
			old_data = ft_strdup(data);
		}
		free(data);
		data = ft_strdup(ft_strjoin(pwd, cwd));
	}
	if (find_var(vars->exp_lst, pwd))
	{
		data = pwd_data(vars->exp_lst, pwd);
		if (!find_var(vars->exp_lst, oldpwd))
			add_tail(vars->exp_lst, ft_strdup(data));
		else
		{
			old_data = pwd_data(vars->exp_lst, oldpwd);
			free (old_data);
			old_data = ft_strdup(data);
		}
		free(data);
		data = ft_strdup(ft_strjoin(pwd, cwd));
	}
}
