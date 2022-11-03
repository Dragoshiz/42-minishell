/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dimbrea <dimbrea@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 10:23:30 by dimbrea           #+#    #+#             */
/*   Updated: 2022/11/03 10:31:33 by dimbrea          ###   ########.fr       */
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


void	ft_builtins(t_vars *vars, t_iovars *iov, int i)
{
	// if (i == 1)
	// 	ft_built_cd();
	if (i == 2)
		ft_built_pwd();
	if (i == 5)
		ft_built_env(vars);
	else if (i == 6)
	{
		vars->call_minish -= 1;
		if (vars->call_minish == 0)
			exit(0);
	}
	else if (i == 7)
		ft_executable(vars, iov);
}

// TODO checks first argument against list of builtins and returns >0 if true
int	check_builtins(t_vars *vars, t_iovars *iov)
{
	int			i;
	int			len;
	const char	*builtins[9];

	builtins[0] = "echo\0";
	builtins[1] = "cd\0";
	builtins[2] = "pwd\0";
	builtins[3] = "export\0";
	builtins[4] = "unset\0";
	builtins[5] = "env\0";
	builtins[6] = "exit\0";
	builtins[7] = "./minishell\0";
	builtins[8] = NULL;
	i = 0;
	len = ft_strlen(vars->args[0]);
	while (builtins[i])
	{
		if (ft_strncmp(vars->args[0], builtins[i], len + 1) == 0)
		{
			ft_builtins(vars, iov, i);
			return (1);
		}
		i++;
	}
	return (0);
}

void	ft_ctrl(int sig)
{
	if (sig == SIGINT)
	{
		rl_replace_line("", 0);
		rl_on_new_line();
		printf("\n");
		rl_redisplay();
		// signal(SIGINT, SIG_K);
	}
}

int	main(int argc, char *argv[], char *env[])
{
	t_vars		vars;
	t_iovars	iov;

	(void)argc;
	(void)argv;
	(void)env;
	(void)iov;
	//env_list_create(&vars);
	signal(SIGINT, ft_ctrl);
	signal(SIGQUIT, SIG_IGN);
	vars.call_minish = 1;
	vars.env_sh = NULL;
	ft_init_vars(&vars); // TODO needs to be reinitialized after each cycle
	// execve("/Users/dimbrea/Documents/hello",NULL,NULL);
	// perror("");
	ft_cpy_env(&vars, env);
	ft_init_exc(&iov);
	ft_execution(&vars, &iov);
	return (0);
}