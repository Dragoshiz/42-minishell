/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dimbrea <dimbrea@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 14:55:15 by dimbrea           #+#    #+#             */
/*   Updated: 2022/11/20 19:03:24 by dimbrea          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	init_cd(t_vars *vars, t_token *curr, char *oldpwd, char *cwd);
static void	init_pwd(t_vars *vars);
static void	error_messages(t_token *curr);
static void	init_oldpwd(t_vars *vars, char *oldpwd, char *cwd);

void	ft_cd(t_vars *vars)
{
	t_token	*curr;
	char	cwd[MAX_PATH_LEN];
	char	*oldpwd;

	oldpwd = ft_strdup("OLDPWD=");
	if (getcwd(cwd, sizeof(cwd)) == NULL)
		perror("");
	curr = vars->parse->token_list->head;
	if (ft_strncmp(curr->data, "cd", 2) == 0)
	{
		if ((curr->next != NULL && curr->next->pipe_nbr != curr->pipe_nbr)
			|| curr->next == NULL)
		{
			ft_putstr_fd("cd: only a relative or absolute path\n", 2);
			g_exit = 1;
			free(oldpwd);
			return ;
		}
		init_cd(vars, curr, oldpwd, cwd);
	}
	free(oldpwd);
}

static void	init_cd(t_vars *vars, t_token *curr, char *oldpwd, char *cwd)
{
	if (curr->next->pipe_nbr == curr->pipe_nbr && curr->next)
	{
		if (chdir(curr->next->data) == 0)
		{
			init_oldpwd(vars, oldpwd, cwd);
			init_pwd(vars);
			g_exit = 0;
		}
		else
			error_messages(curr);
	}
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
		update_pwd(vars, cwd, pwd);
	if (vars->pwd_tmp != NULL)
	{
		if (find_var(vars->env_list, oldpwd))
			update_oldpwd(vars, oldpwd);
	}
	if (vars->pwd_tmp)
		free(vars->pwd_tmp);
	if (find_var(vars->env_list, oldpwd))
		vars->pwd_tmp = ft_strjoin(pwd, cwd);
	else
		vars->pwd_tmp = NULL;
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

static void	init_oldpwd(t_vars *vars, char *oldpwd, char *cwd)
{
	char	*old;

	if (vars->pwd_tmp == NULL && !(find_var(vars->env_list, oldpwd)))
	{
		old = ft_strjoin(oldpwd, cwd);
		ft_update_exp(vars->exp_lst, old);
		ft_add2env(vars, old);
		free(old);
	}
}
