/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parseline.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfuhlenb <vfuhlenb@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 12:40:48 by vfuhlenb          #+#    #+#             */
/*   Updated: 2022/10/15 20:18:45 by vfuhlenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// # of ENV Elements
// create Link List for ENV
// Strdup for each element

void	set_env_sh(t_vars *vars, char *env[])
{
	t_list	*element;

	vars->env_sh = *ft_lstnew(env[0]);
	printf("list: %s", vars->env_sh->content);
}

// first pass: check for pipes -> quotes

// second pass: expansion of variables

// third pass: extract tokens

void	parseline(t_vars *vars)
{
	printf("Line: %s\n", vars->line);
}