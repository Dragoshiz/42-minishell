/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dimbrea <dimbrea@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 12:35:34 by vfuhlenb          #+#    #+#             */
/*   Updated: 2022/11/16 22:42:04 by dimbrea          ###   ########.fr       */
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

void	ft_start_exec(t_vars *vars, t_iovars *iov, t_parsing *parse)
{
	ft_execution(vars, iov, parse);
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

void	ft_execution(t_vars *vars, t_iovars *iov, t_parsing *parse)
{
	while (1)
	{
		vars->line = readline("minish >");
		if (!vars->line)
		{
			write(1, "exit\n", 5);
			break ;
		}
		if (*vars->line && !is_whitespace(vars->line))
		{
			add_history(vars->line);
			ft_init_vars(vars);
			ft_get_path(vars, vars->env_sh);
			parsing(parse, vars);
			if (!vars->syntax_error)
				ft_execv2(parse, iov);
			parsing_cleanup(parse);
			if (iov->vars->paths)
				ft_free_doublepoint(iov->vars->paths);
		}
		if (vars->line)
			free(vars->line);
	}
	cleanup(vars, iov, parse);
}
