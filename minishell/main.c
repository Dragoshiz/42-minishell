/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dimbrea <dimbrea@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 10:23:30 by dimbrea           #+#    #+#             */
/*   Updated: 2022/11/21 13:56:48 by dimbrea          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_exit;

void	ft_init_vars(t_vars *vars)
{
	vars->num_env_sh = 0;
	vars->syntax_error = 0;
	vars->s_err_c = 0;
	vars->is_dir = 0;
}

static void	exit_message(char *str)
{
	ft_putstr_fd("minishell: exit: ", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd(": numeric argument required\n", 2);
}

static void	exit_cleanup(t_iovars *iov)
{
	if (iov->vars->is_cmds)
		ft_free_doublepoint(iov->vars->cmds);
	close(iov->tmpin);
	close(iov->tmpout);
	parsing_cleanup(iov->vars->parse);
	cleanup(iov->vars, iov, iov->vars->parse);
	if (iov->vars->paths)
		ft_free_doublepoint(iov->vars->paths);
}

void	ft_exit(t_token *current, t_iovars *iov)
{
	int	digit;
	int	i;

	i = -1;
	digit = 0;
	if (current->next)
	{
		while (current->next->data[++i])
		{
			if (!ft_isdigit(current->next->data[i]))
			{
				exit_message(current->next->data);
				exit_cleanup(iov);
				exit(255);
			}
		}
		digit = ft_atoi(current->next->data);
		g_exit = digit % 256;
	}
	exit_cleanup(iov);
	exit(digit);
}

int	main(int argc, char *argv[], char *env[])
{
	t_vars		vars;
	t_iovars	iov;
	t_parsing	parsing;

	(void)argc;
	(void)argv;
	g_exit = -1;
	signal(SIGINT, ft_ctrl);
	signal(SIGQUIT, SIG_IGN);
	vars.env_sh = NULL;
	iov.vars = &vars;
	vars.parse = &parsing;
	vars.pwd_tmp = NULL;
	ft_init_vars(&vars);
	ft_cpy_env(&vars, env);
	env_list_create(&vars);
	ft_get_export(&iov);
	ft_init_exc(&iov);
	iov.tmpin = dup(STDIN_FILENO);
	iov.tmpout = dup(STDOUT_FILENO);
	ft_execution(&vars, &iov, &parsing);
	close(iov.tmpin);
	close(iov.tmpout);
	return (0);
}
