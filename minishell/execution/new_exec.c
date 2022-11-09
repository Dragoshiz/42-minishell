/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_exec.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dimbrea <dimbrea@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 12:02:50 by dimbrea           #+#    #+#             */
/*   Updated: 2022/11/09 08:46:17 by dimbrea          ###   ########.fr       */
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

int	ft_get_hrdoc(t_token *current, t_iovars *iov)
{
	char		*line;
	char		*delim;
	int			size_delim;
	t_token		*nxt;

	nxt = current;
	if (ft_strlen(current->data) < 3)
		nxt = current->next;
	delim = ft_strtrim(nxt->data, "<<");
	size_delim = ft_strlen(delim);
	pipe(iov->hrdc_pipe);
	while (1)
	{
		line = readline("> ");
		size_delim = ft_size_rl(nxt->data, size_delim);
		if (ft_strncmp(line, delim, size_delim) == 0)
			break ;
		line = ft_custom_strjoin(line, "\n");
		write(iov->hrdc_pipe[1], line, ft_size_rl(line, size_delim));
		free(line);
	}
	free(line);
	free(delim);
	close(iov->hrdc_pipe[1]);
	return (iov->hrdc_pipe[0]);
}

int	ft_get_fin(t_token *current)//it steps here when HEREDOC
{
	int		fdin;
	char	*filename;
	t_token	*nxt;

	nxt = current;
	if (ft_strlen(nxt->data) < 2)
		nxt = current->next;
	filename = ft_strtrim(nxt->data, "<");
	fdin = open(filename, O_RDONLY);
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
	t_token	*nxt;

	nxt = current;
	if (ft_strlen(nxt->data) < 3)
		nxt = current->next;
	filename = ft_strtrim(nxt->data, ">>");
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
	t_token	*nxt;

	nxt = current;
	if (ft_strlen(nxt->data) < 2)
		nxt = current->next;
	filename = ft_strtrim(nxt->data, ">");
	fdout = open(filename, O_RDWR | O_CREAT | O_TRUNC, 0777);
	if (fdout < 0)
	{
		g_exit = 1;
		perror("");
	}
	free(filename);
	return (fdout);
}

int	ft_get_meta(t_token *current, int i, t_iovars *iov)
{
	int	fdin;

	fdin = 0;
	if (i == 0)
	{
		fdin = ft_get_hrdoc(current, iov);
		iov->hv_heredoc = 1;
	}
	if (i == 1)
		fdin = ft_get_fin(current);
	if (i == 2)
		fdin = ft_appnd(current);
	if (i == 3)
		fdin = ft_overwrite(current);
	return (fdin);
}

int	ft_get_inp(t_iovars *iov, t_parsing *parse, int pipe_nbr)
{
	char	*meta[3];
	int		i;
	int		fdin;
	t_token	*current;

	meta[0] = "<<\0";//pipe n change read from pipe.->0
	meta[1] = "<\0";//redirect input->0
	meta[2] = NULL;
	current = parse->token_list->head;
	while (current->pipe_nbr != pipe_nbr)
		current = current->next;
	while (current->pipe_nbr < parse->num_cmds && current->pipe_nbr == pipe_nbr)
	{
		i = 0;
		fdin = 0;
		while (meta[i])
		{
			if (ft_strncmp(current->data, meta[i], ft_strlen(meta[i])) == 0)
				fdin = ft_get_meta(current, i, iov);
			i++;
		}
		if (!current->next)
			break ;
		current = current->next;
	}
	return (fdin);
}

int	ft_get_out(t_iovars *iov, t_parsing *parse, int pipe_nbr)
{
	const char	*meta[3];
	int			i;
	int			fdout;
	t_token		*current;

	meta[0] = ">>\0";//append output->1
	meta[1] = ">\0";//->1
	meta[2] = NULL;
	current = parse->token_list->head;
	while (current->pipe_nbr != pipe_nbr)
		current = current->next;
	i = 0;
	fdout = 1;
	while (current->pipe_nbr == pipe_nbr && current->pipe_nbr == pipe_nbr)
	{
		while (meta[i])
		{
			if (ft_strncmp(current->data, meta[i], ft_strlen(meta[i])) == 0)
				fdout = ft_get_meta(current, i + 2, iov);
			i++;
		}
		if (!current->next)
			break ;
		current = current->next;
	}
	return (fdout);
}

// void	ft_forknexec(t_parsing *parse, t_iovars *iov)
// {
// 	t_token	*current;
// 	int		pid;

// 	current = parse->token_list->head;
// 	pid = fork();
// 	if (pid == 0)
// 	{
// 		if (iov->hv_heredoc)
// 			close(iov->hrdc_pipe[0]);
// 		close()
// 		if (execve(iov->cmd, vars->cmds, vars->env_sh) < 0)
// 			ft_errmsg(vars, 1);
// 	}
// 	waitpid(vars->pid, NULL, 0);
// }

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

// void	ft_get_cmd(t_parsing *parse, t_iovars *iov)
// {
// 	t_token	*current;
// 	t_token	*start;
// 	int		i;

// 	current = parse->token_list->head
// 	i = 0;
// 	while (current != NULL)
// 	{
// 		if (current->data[0] != '<' && current->data[0] != '>')
			
// 	}
// }

// void	ft_forknexec(t_parsing *parse, t_iovars *iov)
// {
// 	int	pid;

// 	pid = fork();
// 	if (pid == 0)
// 	{
// 		if (iov->hv_heredoc)
// 			close(iov->hrdc_pipe[0]);
// 		if(execve(,))
// 	}
// }
void	ft_execv2(t_parsing *parse, t_iovars *iov)
{
	t_token	*current;
	int		i;

	i = 0;
	current = parse->token_list->head;
	ft_create_pipes(parse, iov);
	while (i < parse->num_cmds)
	{
		iov->fdin = ft_get_inp(iov, parse, i);
		iov->fdout = ft_get_out(iov, parse, i);
		if (i != 0)
		{
			close(iov->pipefds[i - 1][1]);
			iov->fdin = iov->pipefds[i - 1][0];
		}
		dup2(STDIN_FILENO, iov->fdin);
		if (i != parse->num_cmds - 1)
			iov->fdout = iov->pipefds[i][1];
		dup2(STDOUT_FILENO, iov->fdout);
		i++;
	}
}
