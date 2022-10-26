/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfuhlenb <vfuhlenb@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 12:39:00 by vfuhlenb          #+#    #+#             */
/*   Updated: 2022/10/27 00:19:43 by vfuhlenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# define PIPE '|'
# define SQUOTE 39
# define DQUOTE 34
# define SPACE 32

void	parsing_pipeline(t_vars *vars);
void	parsing(t_vars *vars);

void	env_list_create(t_vars *vars);

void	get_tokens(t_vars *vars);

// list_sh_utils.c

void	addHead(t_linkedList *list, void *data);
void	addTail(t_linkedList *list, void *data);
void	displayLinkedList(t_linkedList *list);
void	initializeList(t_linkedList *list);
int		countLinkedList(t_linkedList *list);
void	clearLinkedList(t_linkedList **lst, void (*del)(void*));

#endif