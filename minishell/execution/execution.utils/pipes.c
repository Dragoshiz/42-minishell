/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dimbrea <dimbrea@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 11:16:46 by dimbrea           #+#    #+#             */
/*   Updated: 2022/10/24 19:34:47 by dimbrea          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

//ft_creates pipes
void	ft_create_pipes(t_vars *vars)
{
	int	i;

	i = 0;
	vars->pipefds = malloc(sizeof(int *) * vars->num_args - 1);
	while (i < vars->num_args)
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

//counts number of arguments aka simple commands
void	ft_count_args(t_vars *vars)
{
	int	i;

	i = 0;
	while (vars->args[i])
		i++;
	vars->num_args = i;
}

//see  if it is correct
void	ft_get_cmd(t_vars *vars,char *arg)
{
	int		i;
	int		j;
	char	*tempcmd;

	i = 0;
	while (arg[i] && arg[i] != '<' && arg[i] != '>' && arg[i] != '$')
		i++;
	tempcmd = malloc(sizeof(char) * i);
	j = 0;
	while (j < i)
	{
		tempcmd[j] = arg[j];
		j++;
	}
	vars->cmds = ft_split(tempcmd, ' ');
	free(tempcmd);
}

//returns filename NEED TO FREE FILENAME
char	*ft_get_filename(char *arg, int i)
{
	int		start;
	int		diff;
	int		j;
	char	*filename;

	start = i;
	while (arg[i] != ' ')
		i++;
	diff = i - start;
	filename = malloc(sizeof(char) * diff);
	if (!filename)
		perror("");
	j = 0;
	while (j < diff)
		filename[j++] = arg[start++];
	return (filename);
}

//check all of the simple cmd for infile
int	ft_find_in(t_vars *vars)
{
	int		i;
	int		j;
	int		fd;
	char	*filename;

	i = 0;
	while (vars->args[i])
	{
		j = 0;
		while (vars->args[i][j])
		{
			if (vars->args[i][j] == '<' && vars->args[i][j + 1] == ' ')
			{
				vars->hv_infile = 1;
				filename = ft_get_filename(vars->args[i], j + 2);
				fd = open(filename, O_RDONLY);
				if (fd < 0)
					perror("");
				free(filename);
			}
			j++;
		}
		i++;
	}
	return (fd);
}

void	ft_find_io(t_vars *vars, char *arg)
{
	int	i;

	i = 0;
	while (arg[i])
	{
		if (arg[i] == '>' && arg[i + 1] == ' ')
			vars->hv_outfile = 1;
		else if (arg[i] == '>' && arg[i + 1] == '>' && arg[i + 2] == ' ')
			vars->hv_append = 1;
		i++;
	}
}

//after 1 call 0 everything
//check if there is an outfile in the cmd and creates it
int	ft_find_out(t_vars *vars, char *arg)
{
	int		i;
	int		fd;
	char	*filename;

	i = 0;
	while (arg[i])
	{
		if (arg[i] == '>' && arg[i + 1] == ' ')
		{
			vars->hv_outfile = 1;
			filename = ft_get_filename(arg, i + 2);
			fd = open(filename, O_RDWR | O_CREAT | O_TRUNC, 0777);
			free(filename);
			printf("outfile%s\n", filename);
		}
		else if (arg[i] == '>' && arg[i + 1] == '>' && arg[i + 2] == ' ')
		{
			vars->hv_append = 1;
			filename = ft_get_filename(arg, i + 2);
			fd = open(filename, O_RDWR | O_CREAT | O_APPEND, 0777);
			free(filename);
			printf("infile%s\n", filename);
		}
		if (fd < 0)
			perror("");
		i++;
	}
	return (fd);
}

//check if there is an append in the cmd
// int	ft_find_append(t_vars *vars, char *arg)
// {
// 	int		i;
// 	int		fd;
// 	char	*filename;

// 	i = 0;
// 	while (arg[i])
// 	{
// 		if (arg[i] == '>' && arg[i + 1] == '>' && arg[i + 2] != '>')
// 		{
// 			vars->hv_append = i;
// 			filename = ft_get_filename(arg, i + 2);
// 			fd = open(filename, O_RDWR | O_CREAT | O_APPEND, 0777);
// 			if (fd < 0)
// 				perror("");
// 			free(filename);
// 		}
// 		i++;
// 	}
// 	return (fd);
// }

//check if there is an heredoc in the cmd
// need propper function
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
	int	fdout;
	int	numcmds;
	// int	fd_pipe[2];

	tmpin = dup(STDIN_FILENO);
	tmpout = dup(STDOUT_FILENO);
	ft_find_in(vars);
	if (vars->hv_infile)
		fdin = ft_find_in(vars);
	else
		fdin = dup(tmpin);
	numcmds = 0;
	ft_create_pipes(vars);
	while (numcmds < vars->num_args)
	{
		ft_find_io(vars, vars->args[numcmds]);
		ft_get_cmd(vars, vars->args[numcmds]);
		dup2(fdin, STDIN_FILENO);
		close(fdin);
		if (vars->hv_outfile || vars->hv_append)
		{
			fdout = ft_find_out(vars, vars->args[numcmds]);
		}
		else
			fdout = dup(tmpout);
		if (numcmds != vars->num_args - 1)//problem is here somwhere
		{
			if (!vars->hv_outfile || !vars->hv_append)
				fdout = vars->pipefds[numcmds][1];
			if (numcmds != 0)
				fdin = vars->pipefds[numcmds][0];
		}
		dup2(fdout, STDOUT_FILENO);
		close(fdout);
		vars->pid = fork();
		if (vars->pid == 0)
		{
			if (execve(ft_find_arg_path(vars, vars->cmds[0]), vars->cmds, vars->env_sh) < 0)
				perror("");
		}
		ft_free_doublepoint(vars->cmds);
		vars->hv_append = 0;
		vars->hv_outfile = 0;
		numcmds++;
	}
	dup2(tmpin, STDIN_FILENO);
	dup2(tmpout, STDOUT_FILENO);
	close(tmpin);
	close(tmpout);
	waitpid(vars->pid, NULL, 0);
}




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
