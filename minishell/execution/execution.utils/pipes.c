/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dimbrea <dimbrea@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 11:16:46 by dimbrea           #+#    #+#             */
/*   Updated: 2022/10/23 16:20:37 by dimbrea          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"


//check all of the simple cmds for infile
void	ft_find_in(t_vars *vars)
{
	int	i;
	int	j;

	i = 0;
	while (vars->args[i])
	{
		j = 0;
		while (vars->args[i][j])
		{
			if (vars->args[i][j] == '<' && vars->args[i][j + 1] == ' ')
			{
				vars->hv_infile = 1;
				vars->hv_infile_idx[0] = i;
				vars->hv_infile_idx[1] = j;
			}
			j++;
		}
		i++;
	}
}

//after 1 call 0 everything
//check if there is an outfile in the cmd and creates it
int	ft_find_out(t_vars *vars, char *cmd)
{
	int	i;

	i = 0;
	while (cmd[i])
	{
		if (cmd[i] == '>' && cmd[i + 1] != ' ')
		{
			vars->hv_outfile = i;
		}
		i++;
	}
	return (i);
}

//check if there is an append in the cmd
void	ft_find_append(t_vars *vars, char *cmd)
{
	int	i;

	i = 0;
	while (cmd[i])
	{
		if (cmd[i] == '>' && cmd[i + 1] == '>' && cmd[i + 2] != '>')
			vars->hv_append = i;
		i++;
	}
}

//check if there is an heredoc in the cmd
void	ft_find_hdoc(t_vars *vars, char *cmd)
{
	int	i;

	i = 0;
	while (cmd[i])
	{
		if (cmd[i] == '<' && cmd[i + 1] == '<' && cmd[i + 2] == ' ')
			vars->hv_heredoc = i;
		i++;
	}
}

void	ft_io(t_vars *vars)
{
	int	tmpin;
	int	tmpout;
	int	fdin;

	tmpin = dup(STDIN_FILENO);
	tmpout = dup(STDOUT_FILENO);
	ft_find_in(vars);
	if (vars->hv_infile)
	{
		fdin = open()
	}
}


// void	ft_create_pipes(t_vars *vars)
// {
// 	int	i;

// 	i = 0;
// 	vars->pipefds = malloc(sizeof(int *) * vars->num_pipes);
// 	while (i < vars->num_pipes) // create a function for this
// 	{
// 		vars->pipefds[i] = malloc(sizeof(int) * 2);
// 		if (pipe(vars->pipefds[i]) < 0)
// 		{
// 			perror("error piping");
// 			exit(2);
// 		}
// 		i++;
// 	}
// }

// void	ft_pipeio(t_vars *vars, char **cmd, int cmd_count, int i)
// {
// 	int	tmpin;
// 	// int	tmpout;

// 	if (vars->pid == 0)
// 	{
// 		if (cmd_count == vars->num_cmds - 1 || cmd_count != 0)//2nd to last
// 		{
// 			dup2(vars->pipefds[cmd_count - 1][0], STDIN_FILENO);
// 			if (vars->hv_infile)
// 			{
// 				tmpin = open(ft_strtrim(vars->args[vars->hv_infile], "< "), O_RDONLY);
// 				if (tmpin < 0)
// 					perror("");
// 				dup2(tmpin, STDIN_FILENO);
// 				close(tmpin);
// 			}
// 			if (vars->hv_outfile >= vars->index_pipe[i++])
// 			{
// 				// tmpout = open(ft_strtrim(vars->args[vars->hv_outfile], "> "), O_RDWR | O_CREAT | O_TRUNC, 0777);
// 				// if (tmpout < 0)
// 					// perror("");
// 				dup2(vars->outfd, STDOUT_FILENO);
// 				close(vars->one_cmd);
// 			}
// 		}
// 		if (cmd_count == 0 || cmd_count != vars->num_cmds - 1)//1st to middle
// 		{
// 			dup2(vars->pipefds[cmd_count][1], STDOUT_FILENO);
// 		}
// 		ft_close_pipes(vars);
// 		if (execve(ft_find_arg_path(vars, cmd[0]), cmd, vars->env_sh) < 0)
// 			perror("");
// 	}
// 	else if (vars->pid < 0)
// 		perror("");
// }

// void	ft_close_pipes(t_vars *vars)
// {
// 	int	i;

// 	i = 0;
// 	while (i < vars->num_pipes)
// 	{
// 		close(vars->pipefds[i][0]);
// 		close(vars->pipefds[i][1]);
// 		i++;
// 	}
// }
