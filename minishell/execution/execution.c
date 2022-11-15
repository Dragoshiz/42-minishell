/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dimbrea <dimbrea@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 12:35:34 by vfuhlenb          #+#    #+#             */
/*   Updated: 2022/11/15 15:16:34 by dimbrea          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_init_exc(t_iovars *iov)
{
	iov->filename = NULL;
	iov->size_delim = 0;
	iov->tmpin = 0;
	iov->tmpout = 0;
	iov->fdin = 0;
	iov->fdout = 1;
}

void	ft_start_exec(t_vars *vars, t_iovars *iov, t_parsing *parse)
{
	ft_get_path(vars, vars->env_sh);
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
			parsing(parse, vars);
			if (!vars->syntax_error)
				ft_execv2(parse, iov);
			parsing_cleanup(parse);
			ft_free_doublepoint(vars->args);
		}
		if (vars->line)
			free(vars->line);
	}
	delete_list(vars->exp_lst);
	free(vars->exp_lst);
	delete_list(vars->env_list);
	free(vars->env_list);
	ft_free_doublepoint(vars->env_sh);
	ft_close_pipes(parse, iov);
	ft_free_doublepoint(vars->paths);
}
