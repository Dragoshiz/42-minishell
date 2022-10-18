/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dimbrea <dimbrea@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 10:23:30 by dimbrea           #+#    #+#             */
/*   Updated: 2022/10/18 16:39:10 by dimbrea          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//order
//1-get num of commands
//2-get num of metachar

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
	{
		if (ft_isalpha(vars->args[i][0]))
			vars->num_cmds++;
		i++;
	}
	vars->num_args = i;
}

//function that check if command exists
//function needs to be redone as we don't need to check
//beforehand if command exist++++++++++++++++++++++++++
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
//function needs to be redone or replaced as we don't need to check
//beforehand if command exist++++++++++++++++++++++++++
void	ft_check_cmd(t_vars *vars)
{
	int		i;
	int		j;
	char	**cmd;

	i = 0;
	j = 0;
	vars->cmds = malloc(sizeof(char *) * vars->num_cmds);//free vars->cmds
	while (vars->args[i])
	{
		if (ft_isalpha(vars->args[i][0]))
		{
			vars->cmds[j++] = ft_strdup(vars->args[i]);
			cmd = ft_split(vars->args[i], ' ');
			if (!ft_is_a_cmd(vars->paths, cmd[0]))
			{
				printf("minishell: command not found: %s", vars->args[i]);
				exit(2);
			}
			ft_free_doublepoint(cmd);
		}
		i++;
	}
	i = 0;
}

int	main (int argc, char *argv[], char *env[])
{
	t_vars	vars;
	int		i;

	i = 0;
	(void)argc;
	(void)argv;
	vars.args = malloc(sizeof(char *) * 3);
	while (i < 1)
		vars.args[i++] = malloc(sizeof(char) * 15);
	vars.args[0] = "ls -la";
	vars.args[1] = "|";
	vars.args[2] = "grep mini";
	ft_init(&vars);
	ft_get_path(&vars, env);
	ft_count_args(&vars);
	ft_check_cmd(&vars);
	ft_cpy_env(&vars, env);
	ft_iter(&vars);
	initialize_env_sh_list(&vars, env);
	displayLinkedList(&vars.env_sh_list);
	while (1)
	{
		vars.line = readline("minish >");
		if (*vars.line != '\0')
			add_history(vars.line);
		if (*vars.line != '\0' && !is_whitespace(vars.line))
			get_tokens(&vars);
		free(vars.line);
	}
	return (0);
}