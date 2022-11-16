/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfuhlenb <vfuhlenb@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 14:55:15 by dimbrea           #+#    #+#             */
/*   Updated: 2022/11/17 00:09:54 by vfuhlenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	find_var(t_linked_list *list, char *str)
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

static void	update_pwd(t_vars *vars)
{
	char	cwd[MAX_PATH_LEN];
	char	*pwd;
	char	*oldpwd;

	pwd = ft_strdup("PWD=");
	oldpwd = ft_strdup("OLDPWD=");
	if (getcwd(cwd, sizeof(cwd)) == NULL)
		perror("");
	if (!find_var(vars->env_list, pwd))
		add_tail(vars->env_list, ft_strdup(ft_strjoin(pwd, cwd)));
	if (!find_var(vars->exp_lst, pwd))
		add_tail(vars->exp_lst, ft_strdup(ft_strjoin(pwd, cwd)));
	free(pwd);
	free(oldpwd);
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
				ft_putstr_fd("minishell: cd: ", 2);
				ft_putstr_fd(curr->next->data, 2);
				ft_putstr_fd(": No such file or directory\n", 2);
				g_exit = 1;
				return ;
			}
		}
		update_pwd(vars);
		g_exit = 0;
	}
}
