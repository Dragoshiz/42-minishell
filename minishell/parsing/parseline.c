/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parseline.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfuhlenb <vfuhlenb@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 12:40:48 by vfuhlenb          #+#    #+#             */
/*   Updated: 2022/10/18 16:48:10 by vfuhlenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// # of ENV Elements
// create Link List for ENV
// Strdup for each element

// first pass: check for pipes -> quotes

// second pass: expansion of variables

// third pass: extract tokens

// extract tokens from the line
void	get_tokens(t_vars *vars)
{
	(void)vars;
//	printf("Line: %s\n", vars->line);
}