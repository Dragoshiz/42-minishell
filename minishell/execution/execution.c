/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfuhlenb <vfuhlenb@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 12:35:34 by vfuhlenb          #+#    #+#             */
/*   Updated: 2022/11/20 13:18:54 by vfuhlenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_init_exc(t_iovars *iov)
{
	iov->filename = NULL;
	iov->tmpin = 0;
	iov->tmpout = 0;
	iov->fdin = 0;
	iov->fdout = 1;
}

void	ft_ctrl(int sig)
{
	if (sig == SIGINT)
	{
		rl_replace_line("", 0);
		rl_on_new_line();
		write(1, "\n", 1);
		rl_redisplay();
		g_exit = 1;
	}
}

void	ft_close_pipes(t_parsing *parse, t_iovars *iov)
{
	int	i;

	i = 0;
	if (parse->num_cmds > 1)
	{
		while (iov->pipefds[i])
		{
			close(iov->pipefds[i][1]);
			close(iov->pipefds[i][0]);
			i++;
		}
	}
}

static void	ft_execution2(t_vars *vars, t_iovars *iov)
{
	add_history(vars->line);
	ft_init_vars(vars);
	ft_get_path(vars, vars->env_sh);
	parsing(vars->parse, vars);
	if (!vars->syntax_error)
		ft_execv2(vars->parse, iov);
	parsing_cleanup(vars->parse);
	if (iov->vars->paths)
		ft_free_doublepoint(iov->vars->paths);
}

void	ft_execution(t_vars *vars, t_iovars *iov, t_parsing *parse)
{
	while (1)
	{
		vars->line = readline("minishell > ");
		if (!vars->line)
		{
			vars->is_cmds = 0;
			vars->parse->num_cmds = 0;
			write(1, "exit\n", 5);
			break ;
		}
		if (*vars->line && !is_whitespace(vars->line) && \
			handle_lonely_pipe(vars))
			ft_execution2(vars, iov);
		free(vars->line);
	}
	cleanup(vars, iov, parse);
}
