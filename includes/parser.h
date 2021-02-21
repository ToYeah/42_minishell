/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfukada <nfukada@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/18 10:55:56 by nfukada           #+#    #+#             */
/*   Updated: 2021/02/21 14:04:53 by nfukada          ###   ########.fr       */
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

t_node			*parse_complete_command(t_token **tokens);

t_node			*add_parent_node(t_node_type type, t_node *left, t_node *right);
t_node			*create_command_node(void);
void			set_command_args(t_command *command, t_token **tokens);

void			print_nodes(t_node *node);
void			print_command_args(t_token *args, int fd);
void			print_node_label(t_node *node, int fd);

t_redirect		*create_redirect(void);
void			add_redirect(t_redirect **list, t_redirect *new);

#endif
