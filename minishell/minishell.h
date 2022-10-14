/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dimbrea <dimbrea@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 13:25:23 by dimbrea           #+#    #+#             */
/*   Updated: 2022/10/14 15:32:53 by dimbrea          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include <stdio.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>

# define WHITESPACE " \t"

typedef struct s_vars{
	char	**paths; // ENV list
	char	**args; // array of commands for the executor
	char	*line;
	char	*cmd;
	int		num_args;
	int		num_pipes;
}t_vars;

/*
parseline.c
*/

// returns cmd tree/line for the executor
void	parseline(t_vars *vars);

#endif