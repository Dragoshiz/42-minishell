/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dimbrea <dimbrea@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 16:27:13 by dimbrea           #+#    #+#             */
/*   Updated: 2022/11/19 21:11:25 by dimbrea          ###   ########.fr       */
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
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		ft_putstr_fd(curr->data, STDERR_FILENO);
		ft_putstr_fd(": Is a directory\n", STDERR_FILENO);
		closedir(dir);
	}
	if (!iov->vars->cmds[0])
		return (cmd_path);
	cmd_path = ft_find_arg_path(iov->vars, iov->vars->cmds[0]);
	return (cmd_path);
}

static void	ft_part1exec(t_parsing *parse, t_iovars *iov, t_token *curr, int i)
{
	while (curr->pipe_nbr != i)
			curr = curr->next;
	iov->fdin = ft_get_inp(iov, parse, i);
	iov->fdout = ft_get_out(iov, parse, i);
	if (!check_builtins(curr, iov, i))
		ft_get_cmd(parse, iov, curr, i);
	if (iov->hv_heredoc)
		iov->fdin = iov->hrdc_pipe[0];
	else if (i != 0 && !iov->hv_builtin)
	{
		close(iov->pipefds[i - 1][1]);
		iov->fdin = iov->pipefds[i - 1][0];
	}
	if (iov->fdin == 0)
	{
		if (i != 0 && iov->hv_builtin)
			close(close(iov->pipefds[i - 1][1]));
		dup2(iov->tmpin, STDIN_FILENO);
	}
	else
		dup2(iov->fdin, STDIN_FILENO);
}

void	ft_execv2(t_parsing *parse, t_iovars *iov)
{
	t_token	*curr;
	int		i;

	i = 0;
	iov->hv_heredoc = 0;
	curr = parse->token_list->head;
	ft_create_pipes(parse, iov);
	while (i < parse->num_cmds)
	{
		iov->vars->is_cmds = 0;
		ft_part1exec(parse, iov, curr, i);
		if (!iov->hv_builtin && iov->fdin >= 0)
		{
			ft_execv3(iov, parse, i);
			ft_forknexec(parse, iov, curr);
		}
		if (i <= parse->num_cmds - 1 && i != 0)
			close(iov->pipefds[i - 1][0]);
		if (iov->vars->is_cmds)
			ft_free_doublepoint(iov->vars->cmds);
		i++;
	}
}
