/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minish_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfuhlenb <vfuhlenb@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/15 15:10:49 by dimbrea           #+#    #+#             */
/*   Updated: 2022/11/15 17:26:01 by vfuhlenb         ###   ########.fr       */
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

void	ft_free_doublepointi(int **to_free)
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

//counts number of arguments aka simple commands
// void	ft_count_args(t_vars *vars)
// {
// 	int	i;

// 	i = 0;
// 	while (vars->args[i])
// 		i++;
// 	vars->num_args = i;
// }

void	ft_dup2nclose(int fd, int std)
{
	dup2(fd, std);
	close(fd);
}

// void	ft_executable(t_vars *vars, t_iovars *iov, t_parsing *parsing)
// {
// 	ft_execution(vars, iov, parsing);
// }