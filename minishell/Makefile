  # **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dimbrea <dimbrea@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/10/12 16:27:48 by dimbrea           #+#    #+#              #
#    Updated: 2022/10/14 10:47:46 by dimbrea          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

CC = cc
#remember to use the CFLAGS at the end!!
CFLAGS = -Wall -Wextra -Werror -g

RM = rm -f

AF = ar rcs

SRCS = \
execution/execution.utils/minish_utils.c\
execution/execution.utils/pipes.c\
execution/execution.utils/searchers.c\
execution/execution.c\
parsing/parsing.utils/env_sh_list.c\
parsing/parsing.utils/get_tokens.c\
parsing/parsing.utils/list_sh_utils.c\
parsing/parsing.utils/parseline.c\
parsing/parsing.c\
builtins/ft_env.c\
builtins/ft_export.c\
main.c\

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
		make -C libft
		$(CC) $(OBJS) -Llibft -lft -lreadline -o $(NAME)
		make clean

clean:
	$(RM) $(OBJS)
	make clean -C libft

fclean: clean
	$(RM) $(NAME)
	make fclean -C libft

re: fclean all

norminette:
	norminette $(SRCS)