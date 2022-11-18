/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfuhlenb <vfuhlenb@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 10:23:30 by dimbrea           #+#    #+#             */
/*   Updated: 2022/11/18 14:21:20 by vfuhlenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_exit;

void	ft_init_vars(t_vars *vars)
{
	vars->num_env_sh = 0;
	vars->syntax_error = 0;
	vars->s_err_c = 0;
}

void	ft_exit(t_token *current, t_iovars *iov)
{
	int	digit;
	int	i;

	i = 0;
	digit = 0;
	if (current->next)
	{
		while (current->next->data[i])
		{
			if (!ft_isdigit(current->next->data[i]))
			{
				ft_putstr_fd("minishell: exit: ", 2);
				ft_putstr_fd(current->next->data, 2);
				ft_putstr_fd(": numeric argument required\n", 2);
				exit(255);
			}
			i++;
		}
		digit = ft_atoi(current->next->data);
		g_exit = digit % 256;
	}
	close(iov->tmpin);
	close(iov->tmpout);
	cleanup(iov->vars, iov, iov->vars->parse);
	exit(digit);
}

static void	startup_init(t_vars *vars)
{
	vars->pwd_tmp = NULL;
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
	ft_init_vars(&vars);
	startup_init(&vars);
	ft_cpy_env(&vars, env);
	env_list_create(&vars);
	ft_get_export(&iov);
	ft_init_exc(&iov);
	iov.tmpin = dup(STDIN_FILENO);
	iov.tmpout = dup(STDOUT_FILENO);
	ft_start_exec(&vars, &iov, &parsing);
	close(iov.tmpin);
	close(iov.tmpout);
	return (0);
}
