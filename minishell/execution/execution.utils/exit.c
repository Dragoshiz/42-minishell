/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dimbrea <dimbrea@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/30 13:47:09 by dimbrea           #+#    #+#             */
/*   Updated: 2022/11/12 17:56:03 by dimbrea          ###   ########.fr       */
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
