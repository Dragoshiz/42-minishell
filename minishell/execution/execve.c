/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dimbrea <dimbrea@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 16:27:13 by dimbrea           #+#    #+#             */
/*   Updated: 2022/11/21 11:59:09 by dimbrea          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_execve(t_iovars *iov, char *cmd_path)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == 0)
	{
		if (iov->hv_heredoc)
			close(iov->hrdc_pipe[0]);
		if (execve(cmd_path, iov->vars->cmds, iov->vars->env_sh) < 0)
			exit(g_exit);
	}
	waitpid(pid, &status, 0);
	g_exit = WEXITSTATUS(status);
}

void	ft_forknexec(t_parsing *parse, t_iovars *iov, t_token *curr)
{
	char	*cmd_path;

	cmd_path = ft_exe(parse, iov);
	if (!cmd_path || iov->vars->is_dir)
	{
		if (iov->hv_heredoc)
		{
			close(iov->hrdc_pipe[1]);
			close(iov->hrdc_pipe[0]);
		}
		ft_err_n_close(parse, iov, curr, cmd_path);
		return ;
	}
	ft_execve(iov, cmd_path);
	if (cmd_path)
		free(cmd_path);
	dup2(iov->tmpin, STDIN_FILENO);
	dup2(iov->tmpout, STDOUT_FILENO);
	if (iov->hv_heredoc)
		close(iov->hrdc_pipe[0]);
}

static void	ft_exe_err(char *str)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(str, STDERR_FILENO);
	ft_putstr_fd(": Is a directory\n", STDERR_FILENO);
}

char	*ft_exe(t_parsing *parse, t_iovars *iov)
{
	t_token	*curr;
	char	*cmd_path;
	DIR		*dir;

	cmd_path = NULL;
	curr = parse->token_list->head;
	dir = opendir(curr->data);
	if ((curr->data[0] == '.' || curr->data[0] == '/')
		&& access(curr->data, X_OK) == 0 && dir == NULL)
	{
		cmd_path = ft_strdup(curr->data);
		return (cmd_path);
	}
	else if (dir != NULL)
	{
		iov->vars->is_dir = 1;
		g_exit = 126;
		ft_exe_err(curr->data);
		closedir(dir);
	}
	if (!iov->vars->cmds[0])
		return (cmd_path);
	cmd_path = ft_find_arg_path(iov->vars, iov->vars->cmds[0]);
	return (cmd_path);
}
