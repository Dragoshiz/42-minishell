/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minish_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dimbrea <dimbrea@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/15 15:10:49 by dimbrea           #+#    #+#             */
/*   Updated: 2022/10/24 12:35:21 by dimbrea          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

// int	ft_openfile(t_vars *vars)
// {
// 	int	fd;

	
// 	fd = open(ft_strtrim(vars->args[vars->hv_outfile], "> "), O_RDWR
// 			| O_CREAT | O_TRUNC, 0777);
// 	if (fd < 0)
// 		perror("");
// 	return (fd);
// }

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

void	ft_cleanup(t_vars *vars)
{
	ft_free_doublepoint(vars->env_sh);
	ft_free_doublepoint(vars->cmds);
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
			return (cmd_path);
		free(cmd_path);
		i++;
	}
	return (NULL);
}

//create tempfds  for infile and outfiles
// void	ft_exec(t_vars *vars)
// {
// 	char	**cmd;
// 	int		cmd_count;
// 	int		i;

// 	ft_create_pipes(vars);
// 	cmd_count = 0;
// 	i = 0;
// 	while (cmd_count < vars->num_cmds)
// 	{
// 		if (cmd == NULL)
// 			ft_free_doublepoint(cmd);
// 		cmd = ft_split(vars->cmds[cmd_count], ' ');
// 		vars->pid = fork();
// 		ft_pipeio(vars, cmd, cmd_count, i);
// 		cmd_count++;
// 	}
// 	ft_close_pipes(vars);
// 	waitpid(vars->pid, NULL, 0);
// }

//exec for 1 command
// void	ft_exec1(t_vars *vars)
// {
// 	char	**cmd;
// 	int		pipefd[2];
// 	int		tempin;
// 	int		tempout;

// 	cmd = ft_split(vars->args[vars->one_cmd], ' ');
// 	pipe(pipefd);
// 	if (fork() == 0)
// 	{
// 		if (vars->hv_infile)
// 		{
// 			tempin = open(ft_strtrim(vars->args[vars->hv_infile], "< "), O_RDONLY);
// 			if (tempin < 0)
// 				perror("");
// 			if (dup2(tempin, STDIN_FILENO) < 0)
// 				perror("");
// 			close(tempin);
// 		}
// 		else
// 			tempin = dup(STDIN_FILENO);
// 		if (vars->hv_outfile || vars->hv_redirect)
// 		{
// 			tempout = open(ft_strtrim(vars->args[vars->hv_outfile], "> "), O_RDWR | O_CREAT | O_TRUNC, 0777);
// 			if (vars->hv_redirect)
// 				tempout = open(ft_strtrim(vars->args[vars->hv_outfile], ">> "), O_RDWR | O_CREAT | O_APPEND, 0777);
// 			if (tempout < 0)
// 				perror("");
// 			if (dup2(tempout, STDOUT_FILENO) < 0)
// 				perror("");
// 			close(tempout);
// 		}
// 		else
// 			tempout = dup(STDOUT_FILENO);
// 		if (execve(ft_find_arg_path(vars, cmd[0]), cmd, vars->env_sh) < 0)
// 			perror("here");
// 	}
// 	wait(NULL);
// }

//check if there are 2 times the char
// int	ft_double(t_vars *vars, int i)
// {
// 	if (vars->args[i + 1] == vars->args[i] 
// 		&& vars->args[i + 2] != vars->args[i])
// 		return (0);
// 	return (1);
// }

// //keeping track of number of pipes and commands for the loop
// int	ft_check_pipes(t_vars *vars)
// {
// 	if (vars->num_pipes != vars->num_cmds - 1)
// 		return (1);
// 	return (0);
// }

// void	ft_assign_symbs(t_vars *vars, char arg, int i)
// {
// 	int j;

// 	j = 0;
// 	if (arg == '$')
// 		printf("DOLLA at index %d\n", i);
// 	else if (arg == '<')
// 	{
// 		printf("SMALLER at index %d\n", i);
// 		if (ft_double(vars, i))
// 			vars->hv_heredoc = 1;
// 		vars->hv_infile = i; //need function to find place of file
// 	}
// 	else if (arg == '>')
// 	{
// 		printf("BIGGER at index %d\n", i);
// 		if (ft_double(vars, i))
// 			vars->hv_redirect = 1;
// 		vars->hv_outfile = i;//need function to find place of file
// 		if (vars->hv_outfile != 0)
// 			vars->outfd = ft_openfile(vars);
// 	}
// 	else if (arg == '\'')
// 		printf("SINGLEQ at index %d\n", i);
// 	else if (arg == '\"')
// 		printf("DOUBLEQ at index %d\n", i);
// 	if (arg == '|')
// 	{	
// 		vars->num_pipes++;
// 		vars->index_pipe[j++] = i;
// 		ft_check_pipes(vars);
// 	}
// }

//function that iterates through arguments and find if there are symbols
// void	ft_iter(t_vars *vars)
// {
// 	int		i;
// 	int		j;
// 	char	*symbs;

// 	i = 0;
// 	j = 0 ;
// 	symbs = "|$<>\'\"";
// 	while (vars->args[i])
// 	{
// 		j = 0;
// 		while (symbs[j])
// 		{
// 			if (vars->args[i][0] == symbs[j])
// 				ft_assign_symbs(vars, vars->args[i][0], i);
// 			j++;
// 		}
// 		i++;
// 	}
// 	if (vars->num_cmds == 1)
// 		ft_exec1(vars);
// 	ft_exec(vars);
// }
