/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minish_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dimbrea <dimbrea@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/15 15:10:49 by dimbrea           #+#    #+#             */
/*   Updated: 2022/10/17 17:02:14 by dimbrea          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free_doublepoint(char **to_free)
{
	int	i;

	i = 0;
	while (to_free[i])
	{
		free(to_free[i]);
		i++;
	}
	free(to_free);
}

//copies env in the vars->env
//free vars->env at the end
void	ft_cpy_env(t_vars *vars, char **env)
{
	int	i;

	i = 0;
	while (env[i])
		i++;
	vars->env_sh = malloc(sizeof(char *) * i + 1);
	i = 0;
	while (env[i])
	{
		vars->env_sh[i] = ft_strdup(env[i]);
		i++;
	}
	// vars->env_sh[i] = "\0"; //seems that does not have to be
}

//trying out should be implemented in ft_is_a_cmd()
char	*ft_find_arg_path(t_vars *vars, char *arg)
{
	int		i;
	char	*cmd_path;

	i = 0;
	while (vars->paths[i])
	{
		cmd_path = ft_strjoin(vars->paths[i], arg);
		if (access(cmd_path, F_OK) == 0)
		{
			printf("%s", cmd_path);
			return (cmd_path);
		}
		free(cmd_path);
		i++;
	}
	return (NULL);
}

void	ft_exec(t_vars *vars)
{
	int		pid;
	char	*path;
	char	**cmd;

	cmd = ft_split(vars->args[0], ' ');
	path = ft_find_arg_path(vars, cmd[0]);
	pid = fork();
	if (pid < 0)
	{
		printf("the forking failed\n");
		exit(2);
	}
	if (pid == 0)
	{
		if (execve(path, cmd, vars->env_sh) == -1)
		{
			printf("command didn't execute\n");
			exit(2);
		}
	}
	waitpid(pid, NULL, 0);
}

void	ft_pipe(t_vars *vars, int i)
{
	int		pid;
	int		pid2;
	int		fd[2];
	int		fd_in;
	int		fd_out;
	char	*path;
	char	**cmd;

	if (!vars->args[i + 1])
	{
		printf("HERE\n");
		return ;
	}
	if (pipe(fd) < 0)
		printf("Error piping\n"); //and then exi
	cmd = ft_split(vars->args[i - 1], ' ');
	pid = fork();
	if (pid < 0 )
		printf("Forking failed\n"); //then exit
	if (pid == 0)
	{
		dup2(fd[1], STDOUT_FILENO);
		close(fd[0]);
		close(fd[1]);
		if(!execve(ft_find_arg_path(vars,cmd[0]) , cmd, vars->env_sh))
			printf("Error while executing\n");//then exit
		printf("%s\n", cmd[0]);
	}
	ft_free_doublepoint(cmd);
	free(path);
	cmd = ft_split(vars->args[i + 1], ' ');
	pid2 = fork();
	if (pid2 < 0)
		printf("Forking failed\n"); //then exit
	if (pid2 == 0)
	{
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
		close(fd[1]);
		if(!execve(ft_find_arg_path(vars,cmd[0]), cmd, vars->env_sh))
			printf("Error while executing\n");//then exit
	}
	close(fd[0]);
	close(fd[1]);
	waitpid(pid, NULL, 0);
	waitpid(pid2, NULL, 0);
}

//keeping track of number of pipes and commands for the loop
// int	ft_check_pipes(t_vars *vars)
// {
// 	if (vars->num_pipes != vars->num_cmds - 1)
// 		return (1);
	
// }

void	ft_assign_symbs(t_vars *vars, char arg, int i)
{
	if (arg == '|')
	{	
		vars->num_pipes++;//need function to initialize struct variables
		ft_check_pipes(vars);
		printf("PIPE number =  %d\n", vars->num_pipes);
		// ft_pipe(vars,i);
	}
	else if (arg == '$')
		printf("DOLLA at index %d\n", i);
	else if (arg == '<')
		printf("SMALLER at index %d\n", i);
	else if (arg == '>')
		printf("BIGGER at index %d\n", i);
	else if (arg == '\'')
		printf("SINGLEQ at index %d\n", i);
	else if (arg == '\"')
		printf("DOUBLEQ at index %d\n", i);
}

//function that iterates through arguments and find if there are symbols
void	ft_iter(t_vars *vars)
{
	int		i;
	int		j;
	char	*symbs;
	
	i = 0;
	j = 0 ;
	symbs = "|$<>\'\"";
	while (vars->args[i])
	{
		j = 0;
		while (symbs[j])
		{
			if (vars->args[i][0] == symbs[j])
				ft_assign_symbs(vars, vars->args[i][0], i);
			j++;
		}
		i++;
	}
	if (i == 1 && vars->args[0][0] != '\0')
		ft_exec(vars);
}
