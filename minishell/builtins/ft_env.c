/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfuhlenb <vfuhlenb@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 14:31:14 by vfuhlenb          #+#    #+#             */
/*   Updated: 2022/10/27 19:05:38 by vfuhlenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// initializes ENV_SH_LIST on startup
void	env_list_create(t_vars *vars) // free env_sh linkedList
{
	int	i;

	// check if env is valid and has content
	initializeList(vars->env_list);
	i = 0;
	while (i < vars->num_env_sh)
	{
		addTail(vars->env_list, vars->env_sh[i]);
		i++;
	}
	vars->num_env_sh = i;
}

// prints the ENV List
void	ft_env(t_vars *vars)
{
	displayLinkedList(vars->env_list);
}
