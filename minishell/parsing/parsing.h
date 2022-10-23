/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfuhlenb <vfuhlenb@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 12:39:00 by vfuhlenb          #+#    #+#             */
/*   Updated: 2022/10/23 16:53:06 by vfuhlenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

void	parsing(t_vars *vars);

void	env_list_create(t_vars *vars);

void	get_tokens(t_vars *vars);

// list_sh_utils.c

void	addHead(t_linkedList *list, void *data);
void	addTail(t_linkedList *list, void *data);
void	displayLinkedList(t_linkedList *list);
void	initializeList(t_linkedList *list);

#endif