/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_tokens.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfuhlenb <vfuhlenb@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 13:34:56 by vfuhlenb          #+#    #+#             */
/*   Updated: 2022/10/20 14:45:18 by vfuhlenb         ###   ########.fr       */
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