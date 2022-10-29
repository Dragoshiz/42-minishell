/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfuhlenb <vfuhlenb@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 10:23:30 by dimbrea           #+#    #+#             */
/*   Updated: 2022/10/30 01:12:42 by vfuhlenb         ###   ########.fr       */
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
	//	vars->env_sh = NULL; TODO if set to NULL it will give segfaults
	vars->num_args = 0;
	vars->num_env_sh = 0;
	vars->hv_append = 0;
	vars->hv_outfile = 0;
	vars->hv_heredoc = 0;
	vars->hv_infile = 0;
}

int	main(int argc, char *argv[], char *env[])
{
	t_vars		vars;
	t_iovars	iov;

	(void)argc;
	(void)argv;
	ft_init_vars(&vars); // TODO needs to be reinitialized after each cycle
	ft_cpy_env(&vars, env);
	//env_list_create(&vars);
	while (1)
	{
		vars.line = readline("minish >");
		if (*vars.line != '\0' && !is_whitespace(vars.line))
		{
			add_history(vars.line);
			ft_init_vars(&vars);
			parsing(&vars);
			execution(&vars, &iov);
			//delete_list(vars.env_list);
			free(vars.line);
		}
	}
	return (0);
}
