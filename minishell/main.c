/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dimbrea <dimbrea@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 10:23:30 by dimbrea           #+#    #+#             */
/*   Updated: 2022/11/16 21:14:01 by dimbrea          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_exit;

//copies env in the vars->env
void	ft_cpy_env(t_vars *vars, char **env)
{
	int	i;

	i = 0;
	while (env[i])
		i++;
	vars->env_sh = ft_calloc((i + 1), sizeof(char *));
	i = 0;
	while (env[i])
	{
		vars->env_sh[i] = ft_strdup(env[i]);
		i++;
	}
	vars->env_sh[i] = NULL;
	vars->num_env_sh = i;
}

//function that checks for whitespace characters
int	is_whitespace(char *line)
{
	while (*line)
	{
		if (*line != 32 && !(*line >= 9 && *line <= 13))
			return (0);
		line++;
	}
	return (1);
}

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
	size_t			len;
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
	len = ft_strlen(current->data);
	while (builtins[i])
	{
		if (ft_strncmp(current->data, builtins[i], len) == 0
			&& len == ft_strlen(builtins[i]))
		{
			iov->hv_builtin = 1;
			ft_builtins(current, iov, i, pipe_num);
			return (1);
		}
		i++;
	}
	return (0);
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
