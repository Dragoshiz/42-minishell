/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfuhlenb <vfuhlenb@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 12:39:00 by vfuhlenb          #+#    #+#             */
/*   Updated: 2022/10/27 18:53:59 by vfuhlenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# define PIPE '|'
# define SQUOTE 39
# define DQUOTE 34
# define SPACE 32

typedef struct s_parsing {
	t_linkedList	*pipeline;
	int				line_len;
	char			*line;
	struct s_vars	*s_vars;
}	t_parsing;

void	parsing(t_vars *vars);

// PARSING UTILITIES

void	line_classifier(t_parsing *parsing);

// PIPELINE UTILITIES

void	fill_args(t_parsing *parsing);

// LINE UTIL

int		peek(char *line, char s, int i);

// LIST UTIL

void	addHead(t_linkedList *list, void *data);
void	addTail(t_linkedList *list, void *data);
void	displayLinkedList(t_linkedList *list);
void	initializeList(t_linkedList *list);
int		countLinkedList(t_linkedList *list);
void	deleteList(t_linkedList *list); // TODO

#endif