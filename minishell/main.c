/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfuhlenb <vfuhlenb@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 10:23:30 by dimbrea           #+#    #+#             */
/*   Updated: 2022/11/14 17:01:25 by vfuhlenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
// #include "execution/execution.h"

//copies env in the vars->env
//free vars->env at the end
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
	vars->num_args = 0;
	vars->num_env_sh = 0;
	vars->hv_append = 0;
	vars->hv_outfile = 0;
	vars->hv_infile = 0;
	vars->syntax_error = 0;
	vars->s_err_c = '\0';
}

void	ft_builtins(t_token *current, t_iovars *iov, int i, int pipe_num)
{
	(void) iov;
	if (i == 0)
		ft_echo(current, iov, pipe_num);
	if (i == 1)
		ft_cd(iov->vars);
	if (i == 2)
		ft_built_pwd();
	if (i == 3)
		ft_export(iov->vars);
	if (i == 4)
		ft_unset(current, iov, pipe_num);
	if (i == 5)
		ft_built_env(iov->vars);
	else if (i == 6)
	{
		exit(0);
	}
	// else if (i == 7)
	// 	ft_executable(vars, iov);
}

// TODO checks first argument against list of builtins and returns >0 if true
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
		if (ft_strncmp(current->data, builtins[i], len) == 0)
		{
			if (len == ft_strlen(builtins[i]))
			{
				iov->hv_builtin = 1;
				ft_builtins(current, iov, i, pipe_num);
				return (1);
			}
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
	g_exit = 0;
	signal(SIGINT, ft_ctrl);
	signal(SIGQUIT, SIG_IGN);
	vars.env_sh = NULL;
	iov.vars = &vars;
	vars.parse = &parsing;
	ft_init_vars(&vars);
	ft_cpy_env(&vars, env);
	env_list_create(&vars);
	ft_get_export(&vars);
	ft_init_exc(&iov);
	ft_start_exec(&vars, &iov, &parsing);
	return (0);
}
