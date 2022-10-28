/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dimbrea <dimbrea@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 12:35:34 by vfuhlenb          #+#    #+#             */
/*   Updated: 2022/10/28 10:15:03 by dimbrea          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//function that puts, "/" after being splitted for every path
void	ft_put_backsl(t_vars *vars)
{
	int	i;

	i = 0;
	while (vars->paths[i])
	{
		vars->paths[i] = ft_strjoin(vars->paths[i], "/");
		i++;
	}
}

//function that splits and stores the PATH variable into struct vars->paths
void	ft_get_path(t_vars *vars, char *env[])
{
	char	*path;
	int		i;
	int		k;
	int		j;

	i = 0;
	while (env[i])
	{
		if (!ft_strncmp(env[i], "PATH", 4))
			path = ft_strdup(env[i]);
		i++;
	}
	vars->paths = ft_split(path, ':');
	i = 5;
	k = ft_strlen(vars->paths[0]);
	j = 0;
	while (i <= k)
	{
		vars->paths[0][j] = vars->paths[0][i];
		i++;
		j++;
	}
	vars->paths[0][j] = '\0';
	ft_put_backsl(vars);
	free(path);
}

//part2 of exec function
void	ft_exec_utils(t_vars *vars, t_iovars *iov, int numcmds)
{
	ft_find_io(vars, iov, vars->args[numcmds]);
	ft_get_cmd(vars, vars->args[numcmds]);
	// fprintf(stderr, "%s\n", vars->cmds[0]);
	// fprintf(stderr, "%d", numcmds);
	if (numcmds != 0)
	{
		close(vars->pipefds[numcmds - 1][1]);
		iov->fdin = vars->pipefds[numcmds - 1][0];
	}
	ft_dup2nclose(iov->fdin, STDIN_FILENO);
	if (vars->hv_outfile || vars->hv_append)
		iov->fdout = ft_find_out(vars, iov, vars->args[numcmds]);
	else
		iov->fdout = dup(iov->tmpout);
	if (numcmds != vars->num_args - 1)
		if (!vars->hv_outfile && !vars->hv_append)
			iov->fdout = vars->pipefds[numcmds][1];
	ft_dup2nclose(iov->fdout, STDOUT_FILENO);
	vars->pid = fork();
	if (vars->pid == 0)
		if (execve(ft_find_arg_path(vars, vars->cmds[0]) \
		, vars->cmds, vars->env_sh) < 0)
		{
			close(iov->hrdc_pipe[0]);
			perror("");

		}
	ft_free_doublepoint(vars->cmds);
	vars->hv_append = 0;
	vars->hv_outfile = 0;
	vars->hv_heredoc = 0;
}

//part1 of exec function
void	ft_exec_cmd(t_vars *vars, t_iovars *iov)
{
	int	numcmds;

	iov->tmpin = dup(STDIN_FILENO);
	iov->tmpout = dup(STDOUT_FILENO);
	ft_find_in(vars, iov);
	ft_find_hrdc(vars, iov);
	if (vars->hv_infile)
			iov->fdin = ft_find_in(vars, iov);
	else if (vars->hv_heredoc)
		iov->fdin = iov->hrdc_pipe[0];
	else
		iov->fdin = dup(iov->tmpin);
	ft_create_pipes(vars);
	numcmds = 0;
	while (numcmds < vars->num_args)
	{
		ft_exec_utils(vars, iov, numcmds);
		numcmds++;
	}
	ft_dup2nclose(iov->tmpin, STDIN_FILENO);
	ft_dup2nclose(iov->tmpout, STDOUT_FILENO);
	ft_close_pipes(vars);
	waitpid(vars->pid, NULL, 0);
}

void	execution(t_vars *vars, t_iovars *iov)
{
	vars->args = malloc(sizeof(char *) * 10);
	vars->args[0] = ft_strdup("cat << hi");
	vars->args[1] = ft_strdup("grep alone > file2");
	// vars->args[2] = ft_strdup("cat file2");	
	vars->args[2] = 0;
	// vars->args[1] = ft_strdup("grep mini << hello");
	// vars->args[2] = ft_strdup("wc");
	// vars->args[3] = 0;
	// vars->args[3] = ft_strdup("grep mini");
	// vars->args[4] = ft_strdup("> file2"); 
	ft_count_args(vars);
	ft_get_path(vars, vars->env_sh);
	ft_exec_cmd(vars, iov);
}
