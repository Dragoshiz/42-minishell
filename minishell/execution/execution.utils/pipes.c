/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dimbrea <dimbrea@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 11:16:46 by dimbrea           #+#    #+#             */
/*   Updated: 2022/10/25 16:51:49 by dimbrea          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_close_pipes(t_vars *vars)
{
	int	i;

	i = 0;
	while (i < vars->num_args -1)
	{
		close(vars->pipefds[i][0]);
		close(vars->pipefds[i][1]);
		i++;
	}
}

//ft_creates pipes
void	ft_create_pipes(t_vars *vars)
{
	int	i;

	i = 0;
	vars->pipefds = malloc(sizeof(int *) * vars->num_args - 1);
	while (i < vars->num_args - 1)
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
void	ft_get_cmd(t_vars *vars, char *arg)
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

//check all of the cmd for infile
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
			if (vars->args[i][j - 1] != '<' && vars->args[i][j] == '<'
				&& vars->args[i][j + 1] == ' ')
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
		if (arg[i - 1] != '>' && arg[i] == '>' && arg[i + 1] == ' ')
			vars->hv_outfile = 1;
		else if (arg[i - 1] != '>' && arg[i] == '>' && arg[i + 1] == '>'
			&& arg[i + 2] == ' ')
			vars->hv_append = 1;
		i++;
	}
}

//check if there is an outfile in the cmd and creates it
int	ft_find_out(t_vars *vars, char *arg)
{
	int		i;
	int		fd;
	char	*filename;

	i = 0;
	while (arg[i])
	{
		if (arg[i - 1] == ' ' && arg[i] == '>' && arg[i + 1] == ' ')
		{
			vars->hv_outfile = 1;
			filename = ft_get_filename(arg, i + 2);
			fd = open(filename, O_RDWR | O_CREAT | O_TRUNC, 0777);
			free(filename);
		}
		else if (arg[i - 1] == ' ' && arg[i] == '>' && arg[i + 1] == '>'
			&& arg[i + 2] == ' ')
		{
			vars->hv_append = 1;
			filename = ft_get_filename(arg, i + 3);
			fd = open(filename, O_RDWR | O_CREAT | O_APPEND, 0777);
			free(filename);
		}
		if (fd < 0)
			perror("");
		i++;
	}
	return (fd);
}

//check if there is an heredoc in the cmd
// need propper function
void	ft_find_hdoc(t_vars *vars, char *cmd)
{
	int	i;

	i = 0;
	while (cmd[i])
	{
		if (cmd[i] == ' ' && cmd[i] == '<' && cmd[i + 1] == '<'
			&& cmd[i + 2] == ' ')
			vars->hv_heredoc = 1;
		i++;
	}
}

void	ft_dup2nclose(int fd, int std)
{
	dup2(fd, std);
	close(fd);
}





void	ft_exec_cmd(t_vars *vars)
{
	int	tmpin;
	int	tmpout;
	int	fdin;
	int	fdout;
	int	numcmds;

	tmpin = dup(STDIN_FILENO);
	tmpout = dup(STDOUT_FILENO);
	ft_find_in(vars);
	if (vars->hv_infile)
		fdin = ft_find_in(vars);
	else
		fdin = dup(tmpin);
	ft_create_pipes(vars);
	numcmds = 0;
	while (numcmds < vars->num_args)
	{
		ft_find_io(vars, vars->args[numcmds]);
		ft_get_cmd(vars, vars->args[numcmds]);
		if (numcmds != 0)
		{
			close(vars->pipefds[numcmds - 1][1]);
			fdin = vars->pipefds[numcmds - 1][0];
		}
		ft_dup2nclose(fdin, STDIN_FILENO);
		if (vars->hv_outfile || vars->hv_append)
			fdout = ft_find_out(vars, vars->args[numcmds]);
		else
			fdout = dup(tmpout);
		if (numcmds != vars->num_args - 1)
			if (!vars->hv_outfile && !vars->hv_append)
				fdout = vars->pipefds[numcmds][1];
		ft_dup2nclose(fdout, STDOUT_FILENO);
		vars->pid = fork();
		if (vars->pid == 0)
		{
			if (execve(ft_find_arg_path(vars, vars->cmds[0]) \
			, vars->cmds, vars->env_sh) < 0)
				perror("");
		}
		ft_free_doublepoint(vars->cmds);
		vars->hv_append = 0;
		vars->hv_outfile = 0;
		numcmds++;
	}
	ft_dup2nclose(tmpin, STDIN_FILENO);
	ft_dup2nclose(tmpout, STDOUT_FILENO);
	ft_close_pipes(vars);
	waitpid(vars->pid, NULL, 0);
}
