/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dimbrea <dimbrea@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 13:25:23 by dimbrea           #+#    #+#             */
/*   Updated: 2022/10/18 09:36:41 by dimbrea          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include <fcntl.h>
# include <stdio.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>

# define WHITESPACE " \t"

typedef struct s_vars{
	char	**paths; // ENV list
	char	**args; // array of commands for the executor
	char	**env_sh;
	char	*line;
	int		num_paths;
	int		num_args;
	int		num_cmds;
	int		num_pipes;
	int		hv_infile;
	int		hv_outfile;
	int		hv_redirect;
	int		hv_heredoc;
}t_vars;

/*
parseline.c
*/

// returns cmd tree/line for the executor
void	parseline(t_vars *vars);
void	ft_free_doublepoint(char **to_free);
void	ft_assign_symbs(t_vars *vars, char arg, int i);//try
void	ft_iter(t_vars *vars);//try
void	ft_cpy_env(t_vars *vars, char **env);
void	ft_exec(t_vars *vars);
#endif