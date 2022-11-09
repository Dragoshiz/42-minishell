/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_exec.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dimbrea <dimbrea@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 12:02:50 by dimbrea           #+#    #+#             */
/*   Updated: 2022/11/09 21:02:22 by dimbrea          ###   ########.fr       */
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
		if ((ft_strncmp(line, delim, size_delim) == 0)
			&& (ft_strlen(line) == size_delim))
			break ;
		line = ft_custom_strjoin(line, "\n");
		write(iov->hrdc_pipe[1], line, ft_strlen(line));
		free(line);
	}
	free(line);
	iov->hv_heredoc = 1;
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
	if (type == 2)
		fd = ft_appnd(current);
	if (type == 3)
		ft_get_hrdoc(current, iov);
	if (type == 4)
		fd = ft_overwrite(current);
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
	while (curr->pipe_nbr == pipe_nbr)
	{
		if (curr->type == 1 && curr->next && curr->next->pipe_nbr == pipe_nbr)
			fdin = ft_get_meta(curr, 1, iov);
		if (curr->type == 3 && curr->next && curr->next->pipe_nbr == pipe_nbr)
			fdin = ft_get_meta(curr, 3, iov);
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

	curr = parse->token_list->head;
	while (curr->pipe_nbr != pipe_nbr)
		curr = curr->next;
	fdout = 1;
	while (curr->pipe_nbr == pipe_nbr)
	{
		if (curr->type == 2 && curr->next && curr->next->pipe_nbr == pipe_nbr)
			ft_get_meta(curr, 2, iov);
		if (curr->type == 4 && curr->next && curr->next->pipe_nbr == pipe_nbr)
			ft_get_meta(curr, 4, iov);
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
	iov->pipefds = malloc(sizeof(int *) * (parse->num_cmds - 1));
	while (i < parse->num_cmds - 1)
	{
		iov->pipefds[i] = malloc(sizeof(int) * 2);
		if (pipe(iov->pipefds[i]) < 0)
		{
			perror("");
			exit(1);
		}
		i++;
	}
}

char	*ft_find_arg_path(t_vars *vars, char *arg)
{
	int		i;
	char	*cmd_path;

	i = 0;
	cmd_path = NULL;
	while (vars->paths[i])
	{
		if (access(arg, F_OK) == 0)
			return (arg);
		cmd_path = ft_strjoin(vars->paths[i], arg);
		if (access(cmd_path, F_OK) == 0)
			return (cmd_path);
		free(cmd_path);
		i++;
	}
	return (NULL);
}

void	ft_get_cmd(t_parsing *parse, t_iovars *iov, int pipe)
{
	t_token	*curr;
	int		i;

	i = 0;
	curr = parse->token_list->head;
	while (curr != NULL && curr->type != 0)
		curr = curr->next;
	iov->vars->cmds = ft_calloc(count_token_list
			(parse->token_list) + 1, sizeof(char *));
	while (i < count_token_list(parse->token_list) && curr->pipe_nbr == pipe && curr->type == 0)
	{
		iov->vars->cmds[i] = ft_strdup(curr->data);
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
	if (parse->num_cmds != 1)
	{
		while (i < parse->num_cmds)
		{
			close(iov->pipefds[i][0]);
			close(iov->pipefds[i][1]);
			i++;
		}
	}
}

void	ft_forknexec(t_parsing *parse, t_iovars *iov)
{
	int	pid;
	int	status;

	(void)parse;
	ft_close_pipes(parse, iov);
	pid = fork();
	if (pid == 0)
	{
		if (iov->hv_heredoc)
			close(iov->hrdc_pipe[0]);
		if (execve(ft_find_arg_path(iov->vars, iov->vars->cmds[0]), iov->vars->cmds, iov->vars->env_sh) < 0)
			perror("");
	}
	waitpid(pid, &status, 0);
	g_exit = WEXITSTATUS(status);
	if (iov->hv_heredoc)
			close(iov->hrdc_pipe[0]);
	close(iov->fdout);
	dup2(STDIN_FILENO, iov->fdin);
	dup2(STDOUT_FILENO, iov->fdout);
}

void	ft_execv2(t_parsing *parse, t_iovars *iov)
{
	t_token	*current;
	int		i;

	i = 0;
	iov->hv_heredoc = 0;
	current = parse->token_list->head;
	ft_create_pipes(parse, iov);
	while (i < parse->num_cmds)
	{
		iov->fdin = ft_get_inp(iov, parse, i);
		iov->fdout = ft_get_out(iov, parse, i);
		ft_get_cmd(parse, iov, i);
		if (i != 0)
		{
			close(iov->pipefds[i - 1][1]);
			iov->fdin = iov->pipefds[i - 1][0];
		}
		if (iov->hv_heredoc)
		{
			dup2(iov->hrdc_pipe[0], STDIN_FILENO);
			close(iov->hrdc_pipe[0]);
		}
		else
		{
			dup2(iov->fdin, STDIN_FILENO);
			close(iov->fdin);
		}
		if (i != parse->num_cmds - 1)
			iov->fdout = iov->pipefds[i][1];
		dup2(iov->fdout, STDOUT_FILENO);
		ft_forknexec(parse, iov);
		iov->hv_heredoc = 0; //see where to put this
		i++;
	}
}
