/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfuhlenb <vfuhlenb@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 14:31:14 by vfuhlenb          #+#    #+#             */
/*   Updated: 2022/11/02 20:25:57 by vfuhlenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// initializes ENV_SH_LIST on startup
void	env_list_create(t_vars *vars) // TODO free env_sh linkedList
{
	int	i;

	// TODO check if env is valid and has content
	vars->env_list = NULL;
	vars->env_list = calloc(1, sizeof(t_linked_list));
	initialize_list(vars->env_list);
	i = 0;
	while (i < vars->num_env_sh)
	{
		add_tail(vars->env_list, vars->env_sh[i]);
		i++;
	}
	vars->num_env_sh = i;
}

// prints the ENV List
void	ft_env(t_vars *vars)
{
	display_linked_list(vars->env_list);
}
