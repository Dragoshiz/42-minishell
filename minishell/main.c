/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dimbrea <dimbrea@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 10:23:30 by dimbrea           #+#    #+#             */
/*   Updated: 2022/10/30 15:24:20 by dimbrea          ###   ########.fr       */
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
	vars->env_sh = NULL;
}

int	main(int argc, char *argv[], char *env[])
{
	t_vars		vars;
	t_iovars	iov;

	(void)argc;
	(void)argv;
	ft_init_vars(&vars);
	ft_init_exc(&iov);
	ft_cpy_env(&vars, env);
	//env_list_create(&vars);
	while (1)
	{
		vars.line = readline("minish >");
		if (vars.line)
			add_history(vars.line);
		if (*vars.line != '\0' && !is_whitespace(vars.line))
		{
			parsing(&vars);
			execution(&vars, &iov);
		}
		free(vars.line);
		//deleteList(vars.env_list);
	}
	return (0);
}
