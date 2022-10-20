/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dimbrea <dimbrea@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 15:58:11 by dimbrea           #+#    #+#             */
/*   Updated: 2022/10/18 16:46:01 by dimbrea          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_init(t_vars *vars)
{
	vars->num_args = 0;
	vars->num_cmds = 0;
	vars->num_pipes = 0;
	vars->num_env_sh = 0;
	vars->hv_infile = 0;
	vars->hv_outfile = 0;
	vars->hv_redirect = 0;
	vars->hv_heredoc = 0;
}
