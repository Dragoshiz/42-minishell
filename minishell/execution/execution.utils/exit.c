/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dimbrea <dimbrea@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/30 13:47:09 by dimbrea           #+#    #+#             */
/*   Updated: 2022/11/02 12:04:45 by dimbrea          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_built_env(t_vars *vars)
{
	int	i;

	i = 0;
	while (vars->env_sh[i])
	{
		printf("%s\n", vars->env_sh[i]);
		i++;
	}
}

void	ft_built_pwd(void)
{
	char	cwd[MAX_PATH_LEN];

	if (getcwd(cwd, sizeof(cwd)) == NULL)
		perror("");
	printf("%s\n", cwd);
}

// void	ft_builtins(t_vars *vars, t_iovars *iov, int i)
// {
// 	if (i == 2)
// 		ft_built_pwd();
// 	if (i == 5)
// 		ft_built_env(vars);
// 	else if (i == 6)
// 		exit(0);
// 	else if (i == 7)
// 		ft_exe
// }
