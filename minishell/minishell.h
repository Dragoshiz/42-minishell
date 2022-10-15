/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfuhlenb <vfuhlenb@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 13:25:23 by dimbrea           #+#    #+#             */
/*   Updated: 2022/10/15 20:18:09 by vfuhlenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include <stdio.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>

# define WHITESPACE " \t\r\n\v"

typedef struct s_vars{
	char	**paths; // extracted paths from ENV
	char	*env_sh; // working ENV (minishell)
	char	**args; // array of commands for the executor
	char	*line;
	char	*cmd; //maybe delete
	int		num_paths;
	int		num_args;
	int		num_pipes;
}t_vars;


/*
parseline.c
*/

// returns cmd tree/line for the executor

void	parseline(t_vars *vars);
void	set_env_sh(t_vars *vars, char *env[]);
void	ft_free_doublepoint(char **to_free);

#endif