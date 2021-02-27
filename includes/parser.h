/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfukada <nfukada@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/18 10:55:56 by nfukada           #+#    #+#             */
/*   Updated: 2021/02/25 20:45:57 by nfukada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "exec.h"

typedef enum	e_node_type
{
	NODE_COMMAND,
	NODE_PIPE,
	NODE_SEMICOLON,
}				t_node_type;

typedef struct	s_node
{
	t_node_type		type;
	t_command		*command;
	struct s_node	*left;
	struct s_node	*right;
}				t_node;

typedef struct	s_parse_info
{
	t_command		*last_command;
}				t_parse_info;

t_bool			parse_complete_command(t_node **nodes, t_token **tokens);
void			add_copied_token(t_token **list, t_token *original_token);
t_bool			has_token_type(t_token **token, t_token_type type);
t_bool			is_redirect_token(t_token *token);

t_node			*add_parent_node(t_node_type type, t_node *left, t_node *right);
t_node			*create_command_node(t_parse_info *info);
void			set_command_args(t_command *command, t_token **tokens);
void			del_node_list(t_node *node);

void			print_nodes(t_node *node);
void			print_command_args(t_token *args, int fd);
void			print_node_label(t_node *node, int fd);

t_redirect		*create_redirect(void);
void			add_redirect(t_redirect **list, t_redirect *new);
t_bool			set_redirect_type(t_token *token, t_redirect *redirect);
void			del_redirect_list(t_redirect **redirect_p);

#endif
