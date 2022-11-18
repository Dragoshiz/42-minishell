/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfuhlenb <vfuhlenb@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/29 17:36:51 by dimbrea           #+#    #+#             */
/*   Updated: 2022/11/18 19:03:24 by vfuhlenb         ###   ########.fr       */
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
void	ft_get_path(t_vars *vars, char *env_sh[])
{
	char	*path;
	int		i;
	int		j;

	i = -1;
	path = NULL;
	while (env_sh[++i])
	{
		if (ft_strncmp(env_sh[i], "PATH", 4) == 0)
			path = ft_strdup(env_sh[i]);
	}
	if (!path)
	{
		vars->paths = NULL;
		return ;
	}
	vars->paths = ft_split(path, ':');
	i = 4;
	j = -1;
	while (++i <= (int)ft_strlen(vars->paths[0]))
		vars->paths[0][++j] = vars->paths[0][i];
	vars->paths[0][j] = '\0';
	ft_put_backsl(vars);
	free(path);
}
