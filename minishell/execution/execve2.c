/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfuhlenb <vfuhlenb@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/19 17:43:17 by dimbrea           #+#    #+#             */
/*   Updated: 2022/11/21 17:57:22 by vfuhlenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	cleanup(t_vars *vars, t_iovars *iov, t_parsing *parse)
{
	delete_list(vars->exp_lst);
	free(vars->exp_lst);
	delete_list(vars->env_list);
	free(vars->env_list);
	if (vars->pwd_tmp)
		free(vars->pwd_tmp);
	ft_free_doublepoint(vars->env_sh);
	if (g_exit != -1)
	{
		if (parse->num_cmds > 1)
		{
			ft_close_pipes(parse, iov);
			ft_free_doublepointi(iov->pipefds);
		}
	}
}

void	ft_execv3(t_iovars *iov, t_parsing *parse, int i)
{
	if (i != parse->num_cmds - 1)
		iov->fdout = iov->pipefds[i][1];
	if (iov->fdout == 0)
		dup2(iov->tmpout, STDOUT_FILENO);
	else
		dup2(iov->fdout, STDOUT_FILENO);
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
	if (i != 0 && !iov->hv_builtin)
	{
		close(iov->pipefds[i - 1][1]);
		iov->fdin = iov->pipefds[i - 1][0];
	}
	if (iov->fdin == 0)
	{
		if (i != 0 && iov->hv_builtin)
			close((iov->pipefds[i - 1][1]));
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
	if (parse->num_cmds > 1)
		ft_free_doublepointi(iov->pipefds);
}
