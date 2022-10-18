/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dimbrea <dimbrea@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 13:25:23 by dimbrea           #+#    #+#             */
/*   Updated: 2022/10/18 12:25:13 by dimbrea          ###   ########.fr       */
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
	char	**paths; // ENV list
	char	**args; // array of commands for the executor
	char	**env_sh;
	char	**cmd;
	char	*line;
	int		num_paths;
	int		num_args;
	int		num_cmds;
	int		num_pipes;
	int		num_env_sh;
	int		hv_backgrd;
	int		hv_infile;
	int		hv_outfile;
	int		hv_redirect;
	int		hv_heredoc;	
	t_linkedList	env_sh_list; // working ENV (minishell)
}t_vars;

//Initialize
void	initialize_env_sh_list(t_vars *vars, char *env[]);

//Lexer
void	get_tokens(t_vars *vars);

// Export Builtin
void	displayLinkedList(t_linkedList *list);

// Cleanup
void	ft_free_doublepoint(char **to_free);
// free env_sh linkedList

void	ft_assign_symbs(t_vars *vars, char arg, int i);//try
void	ft_iter(t_vars *vars);//try
void	ft_cpy_env(t_vars *vars, char **env);
void	ft_exec(t_vars *vars);

#endif