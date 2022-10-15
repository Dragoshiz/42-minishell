/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parseline.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfuhlenb <vfuhlenb@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 12:40:48 by vfuhlenb          #+#    #+#             */
/*   Updated: 2022/10/15 19:52:18 by vfuhlenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// # of ENV Elements
// create Link List for ENV
// Strdup for each element

void	set_env_sh()

#include "../minishell.h"

// first pass: check for pipes -> quotes

// second pass: expansion of variables

// third pass: extract tokens

void	parseline(t_vars *vars)
{
	printf("Line: %s\n", vars->line);
	printf("ENV: %s\n", vars->env_sh.);
}