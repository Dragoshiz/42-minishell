/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfuhlenb <vfuhlenb@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 14:55:15 by dimbrea           #+#    #+#             */
/*   Updated: 2022/11/18 13:05:21 by vfuhlenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

static void	init_pwd(t_vars *vars)
{
	char	cwd[MAX_PATH_LEN];
	char	*pwd;
	char	*oldpwd;

	pwd = ft_strdup("PWD=");
	oldpwd = ft_strdup("OLD");
	if (getcwd(cwd, sizeof(cwd)) == NULL)
		perror("");
	if (find_var(vars->env_list, pwd))
	{
		update_pwd(vars, cwd, pwd, oldpwd);
	}
	free(pwd);
	free(oldpwd);
}

static void	error_messages(t_token *curr)
{
	ft_putstr_fd("minishell: cd: ", 2);
	ft_putstr_fd(curr->next->data, 2);
	ft_putstr_fd(": No such file or directory\n", 2);
	g_exit = 1;
}

void	ft_cd(t_vars *vars)
{
	t_token	*curr;

	curr = vars->parse->token_list->head;
	if (ft_strncmp(curr->data, "cd", 2) == 0)
	{
		if ((curr->next != NULL && curr->next->pipe_nbr != curr->pipe_nbr)
			|| curr->next == NULL)
		{
			ft_putstr_fd("cd: only a relative or absolute path\n", 2);
			g_exit = 1;
			return ;
		}
		if (curr->next->pipe_nbr == curr->pipe_nbr && curr->next)
		{
			if (chdir(curr->next->data) != 0)
			{
				error_messages(curr);
				return ;
			}
		}
		init_pwd(vars);
		g_exit = 0;
	}
}
