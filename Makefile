# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: totaisei <totaisei@student.42tokyo.jp>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/02/10 18:36:52 by nfukada           #+#    #+#              #
#    Updated: 2021/02/12 14:27:52 by totaisei         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		:= minishell

SRC_DIR		:= srcs
INC_DIR		:= includes
LIBFT_DIR	:= libft
LIBFT		:= $(LIBFT_DIR)/libft.a
INC			:= -I$(INC_DIR) -I$(LIBFT_DIR)

SRCS		:= srcs/utils/error.c srcs/main.c srcs/exec/exec_command.c srcs/builtin/buildin.c 
OBJS		:= $(SRCS:%.c=%.o)
LIBS		:= -lft -L$(LIBFT_DIR)

CC			:= gcc
CFLAGS		:= -Wall -Werror -Wextra $(INC) -g -fsanitize=address

.PHONY: all clean fclean re bonus norm srcs

all		: $(NAME)

$(NAME)	: $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LIBS)

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

bonus	: all

clean	:
	$(MAKE) clean -C $(LIBFT_DIR)
	rm -f $(OBJS)

fclean	: clean
	$(MAKE) fclean -C $(LIBFT_DIR)
	rm -f $(NAME)

re		: fclean all

norm	:
ifeq ($(shell which norminette),)
		~/.norminette/norminette.rb $(SRCS) $(INC_DIR)
else
		norminette $(SRCS) $(INC_DIR)
endif

srcs	:
	sed -i .bak -e "s#^\(SRCS.*= \).*#\1$$(find srcs -name '*.c' -type f | tr '\n' ' ')#" ./Makefile
