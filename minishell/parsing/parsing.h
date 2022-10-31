/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dimbrea <dimbrea@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 12:39:00 by vfuhlenb          #+#    #+#             */
/*   Updated: 2022/10/29 20:35:22 by dimbrea          ###   ########.fr       */
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
	// char			*q_close;
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

void	addHead(t_linkedList *list, void *data);
void	addTail(t_linkedList *list, void *data);
void	displayLinkedList(t_linkedList *list);
void	initializeList(t_linkedList *list);
int		countLinkedList(t_linkedList *list);
void	deleteList(t_linkedList *list); // TODO

#endif