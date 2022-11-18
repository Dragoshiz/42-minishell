/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfuhlenb <vfuhlenb@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/30 13:47:09 by dimbrea           #+#    #+#             */
/*   Updated: 2022/11/18 17:01:53 by vfuhlenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_built_env(t_iovars *iov, int pipe_num)
{
	t_node	*env;

	env = iov->vars->env_list->head;
	while (env != NULL)
	{
		if (iov->vars->parse->num_cmds > 1 && pipe_num \
			!= iov->vars->parse->num_cmds - 1)
		{
			ft_putstr_fd(env->data, iov->pipefds[pipe_num][1]);
			write(iov->pipefds[pipe_num][1], "\n", 1);
		}
		else if (iov->hv_out)
		{
			ft_putstr_fd(env->data, iov->fdout);
			write(iov->fdout, "\n", 1);
		}
		else
		{
			ft_putstr_fd(env->data, STDOUT_FILENO);
			write(STDOUT_FILENO, "\n", 1);
		}
		env = env->next;
	}
}

void	ft_built_pwd(t_iovars *iov, int pipe_num)
{
	char	cwd[MAX_PATH_LEN];

	if (getcwd(cwd, sizeof(cwd)) == NULL)
		perror("");
	if (iov->vars->parse->num_cmds > 1)
	{
		ft_putstr_fd(cwd, iov->pipefds[pipe_num][1]);
		write(iov->pipefds[pipe_num][1], "\n", 1);
	}
	else if (iov->hv_out)
	{
		ft_putstr_fd(cwd, iov->fdout);
		write(iov->fdout, "\n", 1);
	}
	else
	{
		ft_putstr_fd(cwd, STDOUT_FILENO);
		write(STDOUT_FILENO, "\n", 1);
	}
}
