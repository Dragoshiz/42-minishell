/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dimbrea <dimbrea@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 11:16:46 by dimbrea           #+#    #+#             */
/*   Updated: 2022/10/27 19:02:35 by dimbrea          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

//closes pipes
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
	if (vars->num_args != 0)
	{
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
	tempcmd[j] = '\0';
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

int	ft_size_rl(char *line, t_iovars *iov)
{
	int	i;

	i = 0;
	while (line[i])
		i++;
	if (i < iov->size_delim)
		return (iov->size_delim);
	return (i);
}


int	ft_hrdoc(t_vars *vars, t_iovars *iov, char *arg, int i)
{
	char	*line;
	int		size;

	ft_find_delim (vars, iov, arg, i);
	pipe(iov->hrdc_pipe);
	while (1)
	{
		line = readline("> ");
		size = ft_size_rl(line, iov);
		if (ft_strncmp(line, iov->delim, size) == 0)
			break ;
		line = ft_strjoin(line, "\n");
		write(iov->hrdc_pipe[1], line, ft_size_rl(line,iov));
		free (line);
	}
	free(line);
	close(iov->hrdc_pipe[1]);
	return (1);
}