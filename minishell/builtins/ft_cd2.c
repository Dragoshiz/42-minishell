/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfuhlenb <vfuhlenb@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 14:55:15 by dimbrea           #+#    #+#             */
/*   Updated: 2022/11/18 13:03:30 by vfuhlenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// returns char* from PWD, return NULL if not found
static char	*get_pwd(t_linked_list *list, char *str)
{
	t_node	*curr;

	curr = list->head;
	while (curr)
	{
		if (ft_strncmp(curr->data, str, ft_strlen(str)) == 0)
			return (curr->data);
		curr = curr->next;
	}
	return (NULL);
}

// updates PWD and OLDPWD if variables are present
void	update_pwd(t_vars *vars, char *cwd, char *pwd, char *oldpwd)
{
	char	*old_pwd_data;
	char	*pwd_data;

	old_pwd_data = NULL;
	pwd_data = NULL;
	if (find_var(vars->env_list, oldpwd))
	{
		old_pwd_data = ft_strdup(ft_strjoin(oldpwd, \
			get_pwd(vars->env_list, pwd)));
		ft_update_exp(vars->exp_lst, old_pwd_data);
		ft_update_data(vars, old_pwd_data);
	}
	pwd_data = ft_strdup(ft_strjoin(pwd, cwd));
	ft_update_data(vars, pwd_data);
	ft_update_exp(vars->exp_lst, pwd_data);
	free(old_pwd_data);
	free(pwd_data);
}
