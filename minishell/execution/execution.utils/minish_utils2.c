/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minish_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dimbrea <dimbrea@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/15 15:10:49 by dimbrea           #+#    #+#             */
/*   Updated: 2022/11/21 15:00:50 by dimbrea          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_builtins(t_token *current, t_iovars *iov, int i, int pipe_num)
{
	if (i == 0)
		ft_echo(current, iov, pipe_num);
	if (i == 1)
		ft_cd(iov->vars);
	if (i == 2)
		ft_built_pwd(iov, pipe_num);
	if (i == 3)
		ft_export(iov, pipe_num);
	if (i == 4)
		ft_unset(current, iov, pipe_num);
	if (i == 5)
		ft_built_env(iov, pipe_num);
	else if (i == 6)
		ft_exit(current, iov);
}

int	check_builtins(t_token *current, t_iovars *iov, int pipe_num)
{
	int				i;
	const char		*builtins[10];

	builtins[0] = "echo\0";
	builtins[1] = "cd\0";
	builtins[2] = "pwd\0";
	builtins[3] = "export\0";
	builtins[4] = "unset\0";
	builtins[5] = "env\0";
	builtins[6] = "exit\0";
	builtins[7] = NULL;
	i = 0;
	iov->hv_builtin = 0;
	while (builtins[i])
	{
		if (ft_strncmp(current->data, builtins[i], ft_strlen(current->data)) \
			== 0 && ft_strlen(current->data) == ft_strlen(builtins[i]))
		{
			iov->hv_builtin = 1;
			ft_builtins(current, iov, i, pipe_num);
			return (1);
		}
		i++;
	}
	return (0);
}

int	handle_lonely_pipe(t_vars *vars)
{
	char	*p;

	p = ft_strtrim(vars->line, WHITESPACE);
	if (*p == PIPE)
	{
		ft_putstr_fd("minishell: syntax error near unexpected token '|' \n", 2);
		free(p);
		g_exit = 258;
		return (0);
	}
	free(p);
	return (1);
}
