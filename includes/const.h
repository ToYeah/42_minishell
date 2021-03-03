/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   const.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfukada <nfukada@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/10 19:46:48 by nfukada           #+#    #+#             */
/*   Updated: 2021/03/03 14:40:03 by nfukada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONST_H
# define CONST_H

# define SHELL_PROMPT			"\e[32mminishell > \e[0m"

# define STATUS_SYNTAX_ERROR	258
# define STATUS_TOKEN_ERROR		2
# define STATUS_CMD_NOT_FOUND	127

# ifndef DEBUG
#  define DEBUG			FALSE
# endif

#endif
