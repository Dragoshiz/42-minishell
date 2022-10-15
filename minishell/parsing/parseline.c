/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parseline.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfuhlenb <vfuhlenb@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 12:40:48 by vfuhlenb          #+#    #+#             */
/*   Updated: 2022/10/15 14:36:15 by vfuhlenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// first pass: check for pipes -> quotes

// second pass: expansion of variables

// third pass: extract tokens

void	parseline(t_vars *vars, char *env[])
{
	printf("Line: %s\n", vars->line);
}