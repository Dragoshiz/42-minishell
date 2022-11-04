/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dimbrea <dimbrea@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 12:35:34 by vfuhlenb          #+#    #+#             */
/*   Updated: 2022/11/03 17:06:22 by dimbrea          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//sets stdin and stdout
// void	ft_set_stdin(t_iovars *iov)
// {
// 	// iov->tmpin = dup(STDIN_FILENO);
// 	// iov->tmpout = dup(STDOUT_FILENO);
// 	// close(STDIN_FILENO);
// 	// close(STDOUT_FILENO);
// 	if (iov->tmpin < 0 || iov->tmpout < 0)
// 	{
// 		perror("");
// 		exit(2);
// 	}
// }

//uses the fork function and executes
void	ft_forknexec(t_vars *vars, t_iovars *iov)
{
	iov->cmd = ft_find_arg_path(vars, vars->cmds[0]);
	if (!iov->cmd)
	{
		ft_errmsg(vars, 0);
		return ;
	}
	vars->pid = fork();
	if (vars->pid == 0)
	{
		close(iov->fdin);
		close(iov->fdout);
		// close(iov->tmpin);
		// close(iov->tmpout)
		// close(STDIN_FILENO);
		// close(STDOUT_FILENO);
		if (vars->hv_heredoc)
			close(iov->hrdc_pipe[0]);
		if (execve(iov->cmd, vars->cmds, vars->env_sh) < 0)
			ft_errmsg(vars, 1);
	}
	waitpid(vars->pid, NULL, 0);
}

//part2 of exec function
void	ft_exec_utils(t_vars *vars, t_iovars *iov, int numcmds)
{
	ft_find_io(vars, iov, vars->args[numcmds]);
	ft_get_cmd(vars, vars->args[numcmds]);
	if (numcmds != 0)
	{
		close(vars->pipefds[numcmds - 1][1]);
		iov->fdin = vars->pipefds[numcmds - 1][0];
	}
	ft_dup2nclose(iov->fdin, STDIN_FILENO);
	if (vars->hv_outfile || vars->hv_append)
		iov->fdout = ft_find_out(vars, iov, vars->args[numcmds]);
	else
	{
		// iov->fdout = dup(iov->tmpout);
		// close(iov->tmpout);
	}
	// close(iov->fdout);
	if (numcmds != vars->num_args - 1)
		if (!vars->hv_outfile && !vars->hv_append)
			iov->fdout = vars->pipefds[numcmds][1];
	ft_dup2nclose(iov->fdout, STDOUT_FILENO);
	ft_forknexec(vars, iov);
	// close(iov->tmpout);
	ft_free_doublepoint(vars->cmds);
	ft_set_redir(vars);
}

// //part1 of exec function
void	ft_exec_cmd(t_vars *vars, t_iovars *iov)
{
	int	numcmds;

	// ft_set_stdin(iov);
	ft_find_hrdc(vars, iov);
	ft_find_in(vars);
	if (vars->hv_heredoc)
		iov->fdin = iov->hrdc_pipe[0];
	else if (vars->hv_infile)
			iov->fdin = ft_find_in(vars);
	else
	{
		iov->fdin = dup(iov->tmpin);
		close(iov->tmpin);
	}
	// close(iov->fdin);
	ft_create_pipes(vars);
	numcmds = 0;
	while (numcmds < vars->num_args)
	{
		ft_exec_utils(vars, iov, numcmds);
		numcmds++;
	}
	// ft_dup2nclose(iov->tmpin, STDIN_FILENO);
	// ft_dup2nclose(iov->tmpout, STDOUT_FILENO);
	ft_close_pipes(vars);
}

void	ft_init_exc(t_iovars *iov)
{
	iov->filename = NULL;
	iov->size_delim = 0;
	iov->tmpin = 0;
	iov->tmpout = 0;
	iov->fdin = 0;
	iov->fdout = 0;
}

void	ft_start_exec(t_vars *vars, t_iovars *iov)
{
	ft_get_path(vars, vars->env_sh);
	// ft_set_stdin(iov);
	ft_exec_cmd(vars, iov);
}

void	ft_execution(t_vars *vars, t_iovars *iov)
{
	while (1)
	{
		vars->line = readline("minish >");
		if (!vars->line)
			break ;
		if (*vars->line && !is_whitespace(vars->line))
		{
			add_history(vars->line);
			ft_init_vars(vars);
			parsing(vars);
			if (!vars->syntax_error && !check_builtins(vars, iov))
				ft_start_exec(vars, iov);
			// delete_list(vars->env_list);
		}
		// if (vars->line)
		free(vars->line);
	}
}
