/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dimbrea <dimbrea@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 14:55:15 by dimbrea           #+#    #+#             */
/*   Updated: 2022/11/20 19:29:54 by dimbrea          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// updates PWD and OLDPWD if variables are present
void	update_pwd(t_vars *vars, char *cwd, char *pwd)
{
	char	*pwd_data;

	pwd_data = ft_strjoin(pwd, cwd);
	ft_update_data(vars, pwd_data);
	ft_update_exp(vars->exp_lst, pwd_data);
	free(pwd_data);
}

// updates PWD and OLDPWD if variables are present
void	update_oldpwd(t_vars *vars, char *oldpwd)
{
	char	*old_pwd_data;

	old_pwd_data = NULL;
	old_pwd_data = ft_strjoin(oldpwd, vars->pwd_tmp);
	ft_update_exp(vars->exp_lst, old_pwd_data);
	ft_update_data(vars, old_pwd_data);
	free(old_pwd_data);
}

// checks if var beginning with *str exists in *list
int	find_var(t_linked_list *list, char *str)
{
	t_node	*curr;

	curr = list->head;
	while (curr)
	{
		if (ft_strncmp(curr->data, str, ft_strlen(str)) == 0)
			return (1);
		curr = curr->next;
	}
	return (0);
}
