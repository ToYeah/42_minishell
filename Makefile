# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nfukada <nfukada@student.42tokyo.jp>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/02/10 18:36:52 by nfukada           #+#    #+#              #
#    Updated: 2021/03/05 21:07:48 by nfukada          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		:= minishell
NAME_DEBUG	:= minishell_debug

ifdef DEBUG
NAME		:= $(NAME_DEBUG)
endif

SRC_DIR		:= srcs
INC_DIR		:= includes
LIBFT_DIR	:= libft
LIBFT		:= $(LIBFT_DIR)/libft.a
INC			:= -I$(INC_DIR) -I$(LIBFT_DIR)

SRCS		:= srcs/lexer/lexer_general_state.c srcs/lexer/lexer.c srcs/lexer/lexer_quote_state.c srcs/utils/shell_init.c srcs/utils/shlvl_init.c srcs/utils/token_utils.c srcs/utils/token.c srcs/utils/env_utils_get.c srcs/utils/path_canonicalisation.c srcs/utils/env.c srcs/utils/error.c srcs/utils/error_print.c srcs/utils/signal.c srcs/utils/path_utils.c srcs/utils/env_utils.c srcs/utils/env_sort.c srcs/parser/parser_utils.c srcs/parser/redirect.c srcs/parser/print_node_label.c srcs/parser/parser.c srcs/parser/node.c srcs/parser/print_node.c srcs/expander/expander.c srcs/expander/expand_tokens.c srcs/expander/expand_var.c srcs/main.c srcs/exec/exec_command.c srcs/exec/exec.c srcs/exec/build_path_stat.c srcs/exec/command.c srcs/exec/build_path.c srcs/exec/exec_pipe.c srcs/exec/exec_redirect.c srcs/builtin/mini_echo.c srcs/builtin/mini_cd.c srcs/builtin/mini_export.c srcs/builtin/builtin.c srcs/builtin/mini_cd_utils.c srcs/builtin/mini_unset.c srcs/builtin/mini_export_print.c srcs/builtin/mini_env.c srcs/builtin/mini_pwd.c srcs/builtin/mini_exit.c 
OBJS		:= $(SRCS:%.c=%.o)
LIBS		:= -lft -L$(LIBFT_DIR)

CC			:= gcc
CFLAGS		:= -Wall -Werror -Wextra $(INC)

.PHONY: all clean fclean re bonus debug norm srcs

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
	rm -f $(NAME) $(NAME_DEBUG)

re		: fclean all

debug	: clean
	$(MAKE) CFLAGS="$(CFLAGS) -D DEBUG=TRUE -g -fsanitize=address" DEBUG=TRUE
	$(MAKE) clean

norm	:
ifeq ($(shell which norminette),)
	~/.norminette/norminette.rb $(SRCS) $(INC_DIR)
else
	norminette $(SRCS) $(INC_DIR)
endif

srcs	:
	sed -i .bak -e "s#^\(SRCS.*= \).*#\1$$(find srcs -name '*.c' -type f | tr '\n' ' ')#" ./Makefile
