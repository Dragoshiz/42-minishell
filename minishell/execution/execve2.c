/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dimbrea <dimbrea@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/19 17:43:17 by dimbrea           #+#    #+#             */
/*   Updated: 2022/11/19 17:51:49 by dimbrea          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	cleanup(t_vars *vars, t_iovars *iov, t_parsing *parse)
{
	delete_list(vars->exp_lst);
	free(vars->exp_lst);
	delete_list(vars->env_list);
	free(vars->env_list);
	ft_free_doublepoint(vars->env_sh);
	if (g_exit != -1)
	{
		if (parse->num_cmds > 1)
		{
			ft_close_pipes(parse, iov);
			ft_free_doublepointi(iov->pipefds);
		}
	}
}

void	ft_execv3(t_iovars *iov, t_parsing *parse, int i)
{
	if (i != parse->num_cmds - 1)
		iov->fdout = iov->pipefds[i][1];
	if (iov->fdout == 0)
		dup2(iov->tmpout, STDOUT_FILENO);
	else
		dup2(iov->fdout, STDOUT_FILENO);
}
