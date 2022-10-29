/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfuhlenb <vfuhlenb@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 12:39:00 by vfuhlenb          #+#    #+#             */
/*   Updated: 2022/10/29 22:10:06 by vfuhlenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# define PIPE '|'
# define SQUOTE 39
# define DQUOTE 34
// # define SPACE 32

typedef struct s_parsing {
	struct s_vars	*s_vars;
	t_linkedList	*pipeline;
	int				line_len;
	char			*p_start;
	char			*p_end;
	char			*line_end;
	char			*q_open;
	char			quote;
}	t_parsing;

void	parsing(t_vars *vars);

// PARSING UTILITIES

void	line_classifier(t_parsing *parsing);

// PIPELINE UTILITIES

void	fill_args(t_parsing *parsing);

// LINE UTIL

char	*dup_range(char *p_start, char *p_end);
void	check_quotes(t_parsing *parsing, int i);

// LIST UTIL

void	add_head(t_linkedList *list, void *data);
void	add_tail(t_linkedList *list, void *data);
void	display_linked_list(t_linkedList *list);
void	initialize_list(t_linkedList *list);
int		count_linked_list(t_linkedList *list);
void	delete_list(t_linkedList *list); // TODO

#endif