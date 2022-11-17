/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfuhlenb <vfuhlenb@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 14:31:14 by vfuhlenb          #+#    #+#             */
/*   Updated: 2022/11/17 11:00:52 by vfuhlenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// initializes ENV_SH_LIST on startup
void	env_list_create(t_vars *vars)
{
	int	i;

	vars->env_list = NULL;
	vars->env_list = ft_calloc(1, sizeof(t_linked_list));
	initialize_list(vars->env_list);
	i = 0;
	while (i < vars->num_env_sh)
	{
		add_tail(vars->env_list, ft_strdup(vars->env_sh[i]));
		i++;
	}
	vars->num_env_sh = i;
}

// prints the ENV List
void	ft_env(t_vars *vars)
{
	display_linked_list(vars->env_list);
}

void	update_env_sh(t_vars *vars)
{
	int		i;
	t_node	*curr;

	curr = vars->env_list->head;
	i = count_linked_list(vars->env_list);
	ft_free_doublepoint(vars->env_sh);
	vars->env_sh = ft_calloc((i + 1), sizeof(char *));
	i = 0;
	while (curr)
	{
		vars->env_sh[i] = ft_strdup(curr->data);
		i++;
		curr = curr->next;
	}
	vars->env_sh[i] = NULL;
	vars->num_env_sh = i;
}

//copies env to env_sh
void	ft_cpy_env(t_vars *vars, char **env)
{
	int	i;

	i = 0;
	while (env[i])
		i++;
	vars->env_sh = ft_calloc((i + 1), sizeof(char *));
	i = 0;
	while (env[i])
	{
		vars->env_sh[i] = ft_strdup(env[i]);
		i++;
	}
	vars->env_sh[i] = NULL;
	vars->num_env_sh = i;
}
