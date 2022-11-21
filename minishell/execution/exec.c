/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfuhlenb <vfuhlenb@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 12:02:50 by dimbrea           #+#    #+#             */
/*   Updated: 2022/11/21 15:42:27 by vfuhlenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
			return (ft_strdup(arg));
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

int	ft_tokens_inpipe(t_parsing *parse, int pipe)
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

void	ft_get_cmd(t_parsing *parse, t_iovars *iov, t_token *curr, int pipe)
{
	int		i;

	i = 0;
	iov->vars->cmds = NULL;
	while (curr != NULL && curr->type != 0 && curr->pipe_nbr != pipe)
		curr = curr->next;
	if (curr == NULL)
		return ;
	iov->vars->is_cmds = 1;
	iov->vars->cmds = malloc(sizeof(char *) \
	* (ft_tokens_inpipe(parse, pipe) + 1));
	while (curr->pipe_nbr == pipe && curr->type == 0)
	{
		iov->vars->cmds[i] = ft_strdup(curr->data);
		curr->type = 5;
		i++;
		curr = curr->next;
		if (curr == NULL)
			break ;
	}
	iov->vars->cmds[i] = NULL;
}

static char	*ft_ifnext_cmd(t_parsing *parse, t_iovars *iov, t_token	*curr)
{
	(void)parse;
	(void)iov;
	while (curr != NULL && (curr->type != 5 && curr->type != 0))
		curr = curr->next;
	if (curr == NULL)
		return (NULL);
	else if (curr->type == 5 || curr->type == 0)
		return (curr->data);
	return (NULL);
}

void	ft_err_n_close(t_parsing *parse, t_iovars *iov, t_token *curr, \
char *cmd_path)
{
	close(iov->fdin);
	close(iov->fdout);
	dup2(iov->tmpin, STDIN_FILENO);
	dup2(iov->tmpout, STDOUT_FILENO);
	ft_close_pipes(parse, iov);
	g_exit = 0;
	cmd_path = ft_ifnext_cmd(parse, iov, curr);
	if (cmd_path != NULL && !iov->vars->is_dir)
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		ft_putstr_fd(cmd_path, STDERR_FILENO);
		ft_putstr_fd(": command not found\n", STDERR_FILENO);
		g_exit = 127;
	}
	if (iov->hv_heredoc)
	{
		close(iov->hrdc_pipe[1]);
		close(iov->hrdc_pipe[0]);
	}
}
