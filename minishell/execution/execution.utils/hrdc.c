/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hrdc.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dimbrea <dimbrea@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/29 18:14:31 by dimbrea           #+#    #+#             */
/*   Updated: 2022/10/29 18:46:52 by dimbrea          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_set_redir(t_vars *vars)
{
	vars->hv_append = 0;
	vars->hv_heredoc = 0;
	vars->hv_outfile = 0;
}

void	ft_find_hrdc(t_vars *vars, t_iovars *iov)
{
	int	i;

	i = 0;
	while (vars->args[0][i])
	{
		if (vars->args[0][i - 1] != '<' && vars->args[0][i] == '<' && \
		vars->args[0][i + 1] == '<' && vars->args[0][i + 2] == ' ')
		{
			vars->hv_heredoc = 1;
			ft_hrdoc(vars, iov, vars->args[0], i + 3);
		}
		i++;
	}
	if (!vars->hv_heredoc)
		iov->fdin = iov->tmpin;
}

void	ft_find_io(t_vars *vars, t_iovars *iov, char *arg)
{
	int	i;

	i = 0;
	while (arg[i])
	{
		if (arg[i - 1] != '>' && arg[i] == '>' && arg[i + 1] == ' ')
			ft_find_out(vars, iov, arg);
		else if (arg[i - 1] != '>' && arg[i] == '>' && arg[i + 1] == '>' \
			&& arg[i + 2] == ' ')
			ft_find_out(vars, iov, arg);
		else if (arg[i - 1] != '<' && arg[i] == '<' && arg[i + 1] == '<' \
			&& arg[i + 2] == ' ' && !vars->hv_heredoc)
			ft_hrdoc(vars, iov, arg, i + 3);
		i++;
	}
}
