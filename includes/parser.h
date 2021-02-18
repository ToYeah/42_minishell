/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfukada <nfukada@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/18 10:55:56 by nfukada           #+#    #+#             */
/*   Updated: 2021/02/18 15:51:20 by nfukada          ###   ########.fr       */
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
t_node			*create_command_node(t_token **tokens);
void			print_nodes(t_node *node);

#endif
