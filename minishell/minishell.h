/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfuhlenb <vfuhlenb@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 13:25:23 by dimbrea           #+#    #+#             */
/*   Updated: 2022/10/17 17:40:22 by vfuhlenb         ###   ########.fr       */
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

typedef struct s_node {
	void	*data;
	struct	s_node *next;
}	t_node;

typedef struct s_linkedList {
	t_node	*head;
	t_node	*tail;
	t_node	*current;
}	t_linkedList;

typedef struct s_vars{
	char			**paths; // extracted paths from ENV
	t_linkedList	env_sh; // working ENV (minishell)
	char			**args; // array of commands for the executor
	char			*line;
	char			*cmd; //maybe delete
	int				num_paths;
	int				num_args;
	int				num_pipes;
	int				num_env_sh;
}t_vars;

//Initialize
void	initialize_env_sh(t_vars *vars, char *env[]);

//Lexer
void	get_tokens(t_vars *vars);

// Export Builtin
void	displayLinkedList(t_linkedList *list);

// Cleanup
void	ft_free_doublepoint(char **to_free);
// free env_sh linkedList

#endif