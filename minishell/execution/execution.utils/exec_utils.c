/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dimbrea <dimbrea@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/29 17:36:51 by dimbrea           #+#    #+#             */
/*   Updated: 2022/11/11 11:19:35 by dimbrea          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

// function that puts, "/" after being splitted for every path
void	ft_put_backsl(t_vars *vars)
{
	int	i;

	i = 0;
	while (vars->paths[i])
	{
		vars->paths[i] = ft_custom_strjoin(vars->paths[i], "/");
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

// //writes when an error happens
// void	ft_errmsg(t_vars *vars, int i)
// {
// 	write(2, "minishell: ", 11);
// 	write(2, vars->cmds[0], ft_strlen(vars->cmds[0]));
// 	write(2, ": ", 2);
// 	if (i == 1)
// 		perror("");
// 	else
// 		write(2, "command not found\n", 18);
// }

// char	*ft_custom_strjoin(char *s1, char *s2)
// {
// 	char	*p;
// 	int		i;
// 	int		j;

// 	p = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2)) + 1);
// 	if (p == NULL)
// 		return (NULL);
// 	i = 0;
// 	while (s1[i])
// 	{
// 		p[i] = s1[i];
// 		i++;
// 	}
// 	j = 0;
// 	while (s2[j])
// 	{
// 		p[i] = s2[j];
// 		i++;
// 		j++;
// 	}
// 	p[i] = '\0';
// 	if (*s1)
// 		free(s1);
// 	return (p);
// }

// int	ft_hrdoc(t_vars *vars, t_iovars *iov, char *arg, int i)
// {
// 	char	*line;
// 	int		size;

// 	if (!ft_find_delim(vars, iov, arg, i))
// 		return (0);
// 	pipe(iov->hrdc_pipe);
// 	while (1)
// 	{
// 		line = readline("> ");
// 		size = ft_size_rl(line, iov);
// 		if (ft_strncmp(line, iov->delim, size) == 0)
// 			break ;
// 		line = ft_custom_strjoin(line, "\n");
// 		write(iov->hrdc_pipe[1], line, ft_size_rl(line, iov));
// 		free (line);
// 	}
// 	free(line);
// 	close(iov->hrdc_pipe[1]);
// 	return (1);
// }
