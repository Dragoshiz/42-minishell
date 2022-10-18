/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_sh_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfuhlenb <vfuhlenb@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 16:00:05 by vfuhlenb          #+#    #+#             */
/*   Updated: 2022/10/18 16:36:14 by vfuhlenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// initializes ENV_SH_LIST
void	initialize_env_sh_list(t_vars *vars, char *env[]) // free env_sh linkedList
{
	int	i;

	// check if env is valid and has content
	initializeList(&vars->env_sh_list);
	i = 0;
	while (env[i])
	{
		addTail(&vars->env_sh_list, env[i]);
		i++;
	}
	vars->num_env_sh = i;
}
