/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfuhlenb <vfuhlenb@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 12:39:00 by vfuhlenb          #+#    #+#             */
/*   Updated: 2022/10/22 14:38:55 by vfuhlenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

void	parsing(t_vars *vars);

// env_sh_list.c

void	initialize_env_sh_list(t_vars *vars, char *env[]);

// parseline.c

void	get_tokens(t_vars *vars);

// list_sh_utils.c

void	addHead(t_linkedList *list, void *data);
void	addTail(t_linkedList *list, void *data);
void	displayLinkedList(t_linkedList *list);
void	initializeList(t_linkedList *list);

#endif