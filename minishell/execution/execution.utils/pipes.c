/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dimbrea <dimbrea@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 11:16:46 by dimbrea           #+#    #+#             */
/*   Updated: 2022/11/05 16:06:34 by dimbrea          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

//closes pipes
// void	ft_close_pipes(t_vars *vars)
// {
// 	int	i;

// 	i = 0;
// 	while (i < vars->num_args -1)
// 	{
// 		close(vars->pipefds[i][0]);
// 		close(vars->pipefds[i][1]);
// 		i++;
// 	}
// }

//ft_creates pipes
// void	ft_create_pipes(t_vars *vars)
// {
// 	int	i;

// 	i = 0;
// 	if (vars->num_args != 0)
// 	{
// 		vars->pipefds = malloc(sizeof(int *) * vars->num_args - 1);
// 		while (i < vars->num_args - 1)
// 		{
// 			vars->pipefds[i] = malloc(sizeof(int) * 2);
// 			if (pipe(vars->pipefds[i]) < 0)
// 			{
// 				perror("error piping");
// 				exit(2);
// 			}
// 			i++;
// 		}
// 	}
// }

//see  if it is correct
void	ft_get_cmd(t_vars *vars, char *arg)
{
	int		i;
	int		j;
	char	*tempcmd;

	i = 0;
	while (arg[i] && arg[i] != '<' && arg[i] != '>' && arg[i] != '$')
		i++;
	tempcmd = malloc(sizeof(char) * (i + 1));
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
	while (arg[i] && arg[i] != ' ')
		i++;
	diff = i - start;
	filename = malloc(sizeof(char) * (diff + 1));
	if (!filename)
		perror("");
	j = 0;
	while (j < diff)
		filename[j++] = arg[start++];
	filename[j] = '\0';
	return (filename);
}

// int	ft_size_rl(char *line, t_iovars *iov)
// {
// 	int	i;

// 	i = 0;
// 	while (line[i])
// 		i++;
// 	if (i < iov->size_delim)
// 		return (iov->size_delim);
// 	return (i);
// }
