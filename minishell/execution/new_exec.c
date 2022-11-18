/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_exec.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dimbrea <dimbrea@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 12:02:50 by dimbrea           #+#    #+#             */
/*   Updated: 2022/11/17 16:02:14 by dimbrea          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_custom_strjoin(char *s1, char *s2)
{
	char	*p;
	int		i;
	int		j;

	p = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2)) + 1);
	if (p == NULL)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		p[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j])
	{
		p[i] = s2[j];
		i++;
		j++;
	}
	p[i] = '\0';
	if (*s1)
		free(s1);
	return (p);
}

int	ft_size_rl(char *line, int size_delim)
{
	int	i;

	i = 0;
	while (line[i])
		i++;
	if (i < size_delim)
		return (size_delim);
	return (i);
}

void	ft_get_hrdoc(t_token *current, t_iovars *iov)
{
	char		*line;
	char		*delim;
	size_t		size_delim;
	t_token		*curr;

	curr = current->next;
	delim = curr->data;
	curr->type = 8;
	size_delim = ft_strlen(delim);
	pipe(iov->hrdc_pipe);
	while (1)
	{
		line = readline("> ");
		if (!line)
			return ;
		if ((ft_strncmp(line, delim, size_delim) == 0)
			&& (ft_strlen(line) == size_delim))
			break ;
		line = ft_custom_strjoin(line, "\n");
		write(iov->hrdc_pipe[1], line, ft_strlen(line));
		free(line);
	}
	free(line);
	iov->hv_heredoc = 1;
	g_exit = 0;
	close(iov->hrdc_pipe[1]);
}

int	ft_get_fin(t_token *current)
{
	int		fdin;
	char	*filename;
	t_token	*curr;

	curr = current->next;
	fdin = 0;
	if (curr->data == NULL)
		return (fdin);
	filename = ft_strdup(curr->data);
	fdin = open(filename, O_RDONLY);
	curr->type = 8;
	if (fdin < 0)
	{
		g_exit = 1;
		perror("");
	}
	free(filename);
	return (fdin);
}

int	ft_appnd(t_token *current)
{
	int		fdout;
	char	*filename;
	t_token	*curr;

	curr = current->next;
	fdout = 1;
	if (curr->data == NULL)
		return (fdout);
	filename = ft_strdup(curr->data);
	curr->type = 8;
	fdout = open(filename, O_RDWR | O_CREAT | O_APPEND, 0777);
	if (fdout < 0)
	{
		g_exit = 1;
		perror("");
	}
	free(filename);
	return (fdout);
}

int	ft_overwrite(t_token *current)
{
	int		fdout;
	char	*filename;
	t_token	*curr;

	curr = current->next;
	fdout = 1;
	if (curr->data == NULL)
		return (fdout);
	filename = ft_strdup(curr->data);
	curr->type = 8;
	fdout = open(filename, O_RDWR | O_CREAT | O_TRUNC, 0777);
	if (fdout < 0)
	{
		g_exit = 1;
		perror("");
	}
	free(filename);
	return (fdout);
}

int	ft_get_meta(t_token *current, int type, t_iovars *iov)
{
	int	fd;

	fd = 0;
	if (type == 1)
		fd = ft_get_fin(current);
	else if (type == 2)
	{
		fd = ft_overwrite(current);
		iov->hv_out = 1;
	}
	else if (type == 3)
		ft_get_hrdoc(current, iov);
	else if (type == 4)
	{
		fd = ft_appnd(current);
		iov->hv_out = 1;
	}
	return (fd);
}

int	ft_get_inp(t_iovars *iov, t_parsing *parse, int pipe_nbr)
{
	int			fdin;
	t_token		*curr;

	curr = parse->token_list->head;
	while (curr->pipe_nbr != pipe_nbr)
		curr = curr->next;
	fdin = 0;
	while (curr->pipe_nbr == pipe_nbr && curr != NULL)
	{
		if (curr->type == 1 && curr->next && curr->next->pipe_nbr == pipe_nbr)
			fdin = ft_get_meta(curr, curr->type, iov);
		if (curr->type == 3 && curr->next && curr->next->pipe_nbr == pipe_nbr)
			fdin = ft_get_meta(curr, curr->type, iov);
		if (curr->next == NULL)
			break ;
		curr = curr->next;
	}
	return (fdin);
}

int	ft_get_out(t_iovars *iov, t_parsing *parse, int pipe_nbr)
{
	int			fdout;
	t_token		*curr;

	fdout = 0;
	curr = parse->token_list->head;
	while (curr->pipe_nbr != pipe_nbr)
		curr = curr->next;
	iov->hv_out = 0;
	while (curr->pipe_nbr == pipe_nbr && curr != NULL)
	{
		if (curr->type == 2 && curr->next && curr->next->pipe_nbr == pipe_nbr)
			fdout = ft_get_meta(curr, curr->type, iov);
		if (curr->type == 4 && curr->next && curr->next->pipe_nbr == pipe_nbr)
			fdout = ft_get_meta(curr, curr->type, iov);
		if (curr->next == NULL)
			break ;
		curr = curr->next;
	}
	return (fdout);
}

//ft_creates pipes
void	ft_create_pipes(t_parsing *parse, t_iovars *iov)
{
	int	i;

	i = 0;
	if (parse->num_cmds == 1)
		return ;
	iov->pipefds = ft_calloc(sizeof(int *), parse->num_cmds);
	while (i < parse->num_cmds - 1)
	{
		iov->pipefds[i] = ft_calloc(sizeof(int), 2);
		if (pipe(iov->pipefds[i]) < 0)
		{
			perror("");
			g_exit = 1;
		}
		i++;
	}
}

char	*ft_find_arg_path(t_vars *vars, char *arg)
{
	int		i;
	char	*cmd_path;

	i = 0;
	if (!vars->paths)
		return (NULL);
	while (vars->paths[i])
	{
		if (access(arg, F_OK) == 0)
			return (arg);
		cmd_path = ft_strjoin(vars->paths[i], arg);
		if (access(cmd_path, F_OK) == 0)
		{
			return (cmd_path);
		}
		free(cmd_path);
		i++;
	}
	return (NULL);
}

int		ft_tokens_inpipe(t_parsing *parse, int pipe)
{
	t_token	*curr;
	int		i;

	curr = parse->token_list->head;
	while (curr->pipe_nbr != pipe)
		curr = curr->next;
	while (curr != NULL && curr->pipe_nbr == pipe && curr->type != 0)
	{
		curr = curr->next;
		if (curr == NULL)
			break ;
	}
	i = 0;
	while (curr != NULL && curr->type == 0 && curr->pipe_nbr == pipe)
	{
		i++;
		curr = curr->next;
	}
	return (i);
}

static void	ft_get_cmd(t_parsing *parse, t_iovars *iov, t_token *curr, int pipe)
{
	int		i;

	i = 0;
	while (curr != NULL && curr->type != 0 && curr->pipe_nbr != pipe)
		curr = curr->next;
	if (curr == NULL)
		return ;
	iov->vars->cmds = ft_calloc(sizeof(char *), \
		(ft_tokens_inpipe(parse, pipe) + 1));
	while (curr->pipe_nbr == pipe && curr->type == 0)
	{
		iov->vars->cmds[i] = ft_strdup(curr->data);
		curr->type = 8;
		curr = curr->next;
		if (curr == NULL)
			break ;
		i++;
	}
}

void	ft_close_pipes(t_parsing *parse, t_iovars *iov)
{
	int	i;

	i = 0;
	if (parse->num_cmds > 1 )
	{
		while (iov->pipefds[i])
		{
			close(iov->pipefds[i][1]);
			close(iov->pipefds[i][0]);
			i++;
		}
	}
}

void	ft_forknexec(t_parsing *parse, t_iovars *iov)
{
	pid_t	pid;
	int		status;
	char	*cmd_path;

	cmd_path = ft_exe(parse, iov);
	if (!cmd_path)
	{
		close(iov->fdin);
		close(iov->fdout);
		dup2(iov->tmpin, STDIN_FILENO);
		dup2(iov->tmpout, STDOUT_FILENO);
		ft_close_pipes(parse, iov);
		g_exit = 0;
		if (cmd_path)
		{
			ft_putstr_fd("minishell: ", STDERR_FILENO);
			ft_putstr_fd(iov->vars->cmds[0], STDERR_FILENO);
			ft_putstr_fd(": command not found\n", STDERR_FILENO);
			g_exit = 127;
		}
		if (iov->vars->cmds)
			ft_free_doublepoint(iov->vars->cmds);
		if (iov->hv_heredoc)
		{
			close(iov->hrdc_pipe[1]);
			close(iov->hrdc_pipe[0]);
		}
		return ;
	}
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
	dup2(iov->tmpin, STDIN_FILENO);
	dup2(iov->tmpout, STDOUT_FILENO);
	if (iov->hv_heredoc)
		close(iov->hrdc_pipe[0]);
	if (!cmd_path)
		free(cmd_path);
}

char	*ft_exe(t_parsing *parse, t_iovars *iov)
{
	t_token	*curr;
	char	*cmd_path;

	cmd_path = NULL;
	curr = parse->token_list->head;
	if ((curr->data[0] == '.' || curr->data[0] == '/')
		&& access(curr->data, X_OK) == 0)
	{
		cmd_path = curr->data;
	}	
	else if (!iov->vars->cmds[0])
		return (NULL);
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
		ft_part1exec(parse, iov, curr, i);
		// while (curr->pipe_nbr != i)
		// 	curr = curr->next;
		// iov->fdin = ft_get_inp(iov, parse, i);
		// iov->fdout = ft_get_out(iov, parse, i);
		// if (!check_builtins(curr, iov, i))
		// 	ft_get_cmd(parse, iov, curr, i);
		// if (iov->hv_heredoc)
		// 	iov->fdin = iov->hrdc_pipe[0];
		// else if (i != 0 && !iov->hv_builtin)
		// {
		// 	close(iov->pipefds[i - 1][1]);
		// 	iov->fdin = iov->pipefds[i - 1][0];
		// }
		// if (iov->fdin == 0)
		// {
		// 	if (i != 0 && iov->hv_builtin)
		// 		close(close(iov->pipefds[i - 1][1]));
		// 	dup2(iov->tmpin, STDIN_FILENO);
		// }
		// else
		// 	dup2(iov->fdin, STDIN_FILENO);
		if (!iov->hv_builtin && iov->fdin >= 0)
		{
			if (i != parse->num_cmds - 1)
				iov->fdout = iov->pipefds[i][1];
			if (iov->fdout == 0)
				dup2(iov->tmpout, STDOUT_FILENO);
			else
				dup2(iov->fdout, STDOUT_FILENO);
			ft_forknexec(parse, iov);
		}
		if (i <= parse->num_cmds - 1 && i != 0)
			close(iov->pipefds[i - 1][0]);
		// iov->hv_heredoc = 0; //see where to put this
		i++;
	}
}
