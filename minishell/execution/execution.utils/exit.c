/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dimbrea <dimbrea@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/30 13:47:09 by dimbrea           #+#    #+#             */
/*   Updated: 2022/11/07 12:33:13 by dimbrea          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_built_env(t_vars *vars)
{
	t_node	*env;

	env = vars->env_list->head;
	while (env != NULL)
	{
		printf("%s\n", env->data);
		env = env->next;
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
