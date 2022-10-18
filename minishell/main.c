/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfuhlenb <vfuhlenb@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 10:23:30 by dimbrea           #+#    #+#             */
/*   Updated: 2022/10/18 10:16:35 by dimbrea          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

//function that puts, "/" after being splitted for every path
void	ft_put_backsl(t_vars *vars)
{
	int	i;

	i = 0;
	while (vars->paths[i])
	{
		vars->paths[i] = ft_strjoin(vars->paths[i], "/");
		i++;
	}
}

//function that splits and stores the PATH variable into struct vars->paths
void	ft_get_path(t_vars *vars, char *env[])
{
	char	*path;
	int		i;
	int		k;
	int		j;

	i = 0;
	while (env[i])
	{
		if (!ft_strncmp(env[i], "PATH", 4))
			path = ft_strdup(env[i]);
		i++;
	}
	vars->paths = ft_split(path, ':');
	i = 5;
	k = ft_strlen(vars->paths[0]);
	j = 0;
	while (i <= k)
	{
		vars->paths[0][j] = vars->paths[0][i];
		i++;
		j++;
	}
	vars->paths[0][j] = '\0';
	ft_put_backsl(vars);
	free(path);
}

//function that count how many arguments there are
void	ft_count_args(t_vars *vars)
{
	int	i;

	i = 0;
	while (vars->args[i])
		i++;
	vars->num_args = i;
}

//function that check if command exists
int	ft_is_a_cmd(char **paths, char *arg)
{
	char	*cmd;
	int		i;

	i = 0;
	while (paths[i])
	{
		cmd = ft_strjoin(paths[i], arg);
		if (access(cmd, F_OK) == 0)
		{
			free(cmd);
			return (1);
		}
		free(cmd);
		i++;
	}
	return (0);
}

//it iterates through args and check if they exist
void	ft_check_cmd(t_vars *vars)//1st function
{
	int		i;
	char	**cmd;

	i = 0;
	while (vars->args[i])
	{
		if (ft_isalpha(vars->args[i][0]))
		{
			cmd = ft_split(vars->args[i], ' ');
			if (!ft_is_a_cmd(vars->paths, cmd[0]))
			{
				printf("minishell: command not found: %s", vars->args[i]);
				exit(2);
			}
			ft_free_doublepoint(cmd);
			vars->num_cmds++;
		}
		i++;
	}
}

// // FREE THE VARS->LINE, VARS->ARGS
// void	ft_readline(t_vars *vars)
// {
// 	int	i;

// 	vars->line = readline("minish$ ");
// 	add_history(vars->line);
// 	vars->args = ft_split(vars->line, '|');
// 	i = 0;
// 	while (vars->args[i])
// 		printf("%s\n", vars->args[i++]);
// }

int	main(int argc, char *argv[], char *env[])
{
	t_vars	vars;
	int		i;

	vars.args = malloc(sizeof(char *) * 5);
	// while (i < 1)
		vars.args[i++] = malloc(sizeof(char) * 15);
	vars.args[0] = "ls -la";
	vars.args[1] = "|";
	vars.args[2] = "grep mini";
	vars.args[3] = "|";
	vars.args[4] = "<";
	ft_get_path(&vars, env);
	ft_check_cmd(&vars);
	ft_count_args(&vars);
	ft_cpy_env(&vars, env);
	ft_iter(&vars);
  initialize_env_sh(&vars, env);
	//ft_check_cmd(&vars);
  displayLinkedList(&vars.env_sh);
	while (1)
	{
		vars.line = readline("minish$ ");
		if (*vars.line != '\0')
			add_history(vars.line);
		if (*vars.line != '\0' && !is_whitespace(vars.line))
			get_tokens(&vars);
		free(vars.line);
	}
	return (0);
}