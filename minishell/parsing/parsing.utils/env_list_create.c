/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_list_create.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfuhlenb <vfuhlenb@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 16:00:05 by vfuhlenb          #+#    #+#             */
/*   Updated: 2022/10/23 17:28:31 by vfuhlenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

// initializes ENV_SH_LIST on startup
void	env_list_create(t_vars *vars) // free env_sh linkedList
{
	int	i;

	// check if env is valid and has content
	initializeList(vars->env_list);
	i = 0;
	while (vars->env_sh[i])
	{
		addTail(vars->env_list, vars->env_sh[i]);
		i++;
	}
	vars->num_env_sh = i;
}