/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dimbrea <dimbrea@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 10:23:30 by dimbrea           #+#    #+#             */
/*   Updated: 2022/10/31 17:23:51 by dimbrea          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "execution/execution.h"

//copies env in the vars->env
//free vars->env at the end
void	ft_cpy_env(t_vars *vars, char **env)
{
	int	i;

	i = 0;
	while (env[i])
		i++;
	vars->env_sh = malloc(sizeof(char *) * (i + 1));
	i = 0;
	while (env[i])
	{
		vars->env_sh[i] = ft_strdup(env[i]);
		i++;
	}
	vars->env_sh[i] = NULL;
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
	vars->hv_heredoc = 0;
	vars->hv_infile = 0;
	vars->syntax_error = 0;
}

// TODO checks first argument against list of builtins and returns >0 if true
static int	check_builtins(t_vars *vars)
{
	int			i;
	int			len;
	const char	*builtins[8];

	builtins[0] = "echo\0";
	builtins[1] = "cd\0";
	builtins[2] = "pwd\0";
	builtins[3] = "export\0";
	builtins[4] = "unset\0";
	builtins[5] = "env\0";
	builtins[6] = "exit\0";
	builtins[7] = NULL;
	i = 0;
	len = ft_strlen(vars->args[0]);
	while (builtins[i])
	{
		if (ft_strncmp(vars->args[0], builtins[i], len) == 0)
		{
			ft_builtins(vars, i);
			return (1);
		}
		i++;
	}
	return (0);
}

void	ft_ctrl_c(int sig)
{
	rl_replace_line("", sig);
}

int	main(int argc, char *argv[], char *env[])
{
	t_vars		vars;
	t_iovars	iov;

	(void)argc;
	(void)argv;
	//env_list_create(&vars);
	vars.env_sh = NULL;
	ft_init_vars(&vars); // TODO needs to be reinitialized after each cycle
	ft_cpy_env(&vars, env);
	ft_init_exc(&iov);
	while (1)
	{
		vars.line = readline("minish >");
		signal(SIGINT,ft_ctrl_c);
		if (!vars.line)
			break ;
		if (*vars.line && vars.line && !is_whitespace(vars.line))
		{
			add_history(vars.line);
			ft_init_vars(&vars);
			parsing(&vars);
			if (!vars.syntax_error && !check_builtins(&vars))
				execution(&vars, &iov);
			//delete_list(vars.env_list);
		}
		if (vars.line)
			free(vars.line);
	}
	return (0);
}
