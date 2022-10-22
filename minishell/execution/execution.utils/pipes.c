/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfuhlenb <vfuhlenb@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 11:16:46 by dimbrea           #+#    #+#             */
/*   Updated: 2022/10/22 14:12:28 by vfuhlenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_create_pipes(t_vars *vars)
{
	int	i;

	i = 0;
	vars->pipefds = malloc(sizeof(int *) * vars->num_pipes);
	while (i < vars->num_pipes) // create a function for this
	{
		vars->pipefds[i] = malloc(sizeof(int) * 2);
		if (pipe(vars->pipefds[i]) < 0)
		{
			perror("error piping");
			exit(2);
		}
		i++;
	}
}

void	ft_pipeio(t_vars *vars, char **cmd, int cmd_count)
{
	int	tmpin;
	// int	tmpout;

	if (vars->pid == 0)
	{
		if (cmd_count == vars->num_cmds - 1 || cmd_count != 0)
		{
			dup2(vars->pipefds[cmd_count - 1][0], STDIN_FILENO);
			if (vars->hv_infile)
			{
				tmpin = open(ft_strtrim(vars->args[vars->hv_infile], "< "), O_RDONLY);
				if (tmpin < 0)
					perror("file does not exist");
				dup2(tmpin, STDIN_FILENO);
				close(tmpin);
			}
		}
		if (cmd_count == 0 || cmd_count != vars->num_cmds - 1)
			dup2(vars->pipefds[cmd_count][1], STDOUT_FILENO);
		ft_close_pipes(vars);
		if (execve(ft_find_arg_path(vars, cmd[0]), cmd, vars->env_sh) < 0)
			perror("");
	}
	else if (vars->pid < 0)
		perror("");
}

void	ft_close_pipes(t_vars *vars)
{
	int	i;

	i = 0;
	while (i < vars->num_pipes)
	{
		close(vars->pipefds[i][0]);
		close(vars->pipefds[i][1]);
		i++;
	}
}
