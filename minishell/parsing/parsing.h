/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfuhlenb <vfuhlenb@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 12:39:00 by vfuhlenb          #+#    #+#             */
/*   Updated: 2022/10/30 14:32:46 by vfuhlenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# define PIPE '|'
# define SQUOTE 39
# define DQUOTE 34
# define EMPTY_SPACE 32

typedef struct s_parsing {
	struct s_vars	*s_vars;
	t_linked_list	*pipeline;
	int				line_len;
	char			*p_start;
	char			*p_end;
	char			*line_end;
	char			*q_open;
	char			quote;
}	t_parsing;

void	parsing(t_vars *vars);

// PIPELINE UTILITIES

void	fill_args(t_parsing *parsing);
void	check_quotes(t_parsing *parsing, int i);

// LINE UTIL

char	*dup_range(char *p_start, char *p_end);
void	check_quotes(t_parsing *parsing, int i);

// LIST UTIL

void	add_head(t_linked_list *list, void *data);
void	add_tail(t_linked_list *list, void *data);
void	display_linked_list(t_linked_list *list);
void	initialize_list(t_linked_list *list);
int		count_linked_list(t_linked_list *list);
void	delete_list(t_linked_list *list); // TODO also delete sub-list

#endif