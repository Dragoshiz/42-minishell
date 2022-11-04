/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minish_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dimbrea <dimbrea@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/15 15:10:49 by dimbrea           #+#    #+#             */
/*   Updated: 2022/11/03 16:20:11 by dimbrea          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_free_doublepoint(char **to_free)
{
	int	i;

	i = 0;
	while (to_free[i])
	{
		free(to_free[i]);
		i++;
	}
	free(to_free);
}

void	ft_cleanup(t_vars *vars)
{
	ft_free_doublepoint(vars->env_sh);
	ft_free_doublepoint(vars->cmds);
}

//trying out should be implemented in ft_is_a_cmd()
char	*ft_find_arg_path(t_vars *vars, char *arg)
{
	int		i;
	char	*cmd_path;

	i = 0;
	cmd_path = NULL;
	while (vars->paths[i])
	{
		if (access(arg, F_OK) == 0)
			return (arg);
		cmd_path = ft_strjoin(vars->paths[i], arg);
		if (access(cmd_path, F_OK) == 0)
			return (cmd_path);
		free(cmd_path);
		i++;
	}
	return (NULL);
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

void	ft_dup2nclose(int fd, int std)
{
	// (void)std;
	dup2(fd, std);
	close(fd);
	// close(std);
}

void	ft_executable(t_vars *vars, t_iovars *iov)
{
	vars->call_minish += 1;
	ft_execution(vars, iov);
}