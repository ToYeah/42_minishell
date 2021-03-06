/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   const.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfukada <nfukada@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/10 19:46:48 by nfukada           #+#    #+#             */
/*   Updated: 2021/03/12 12:43:55 by nfukada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONST_H
# define CONST_H

# define SHELL_PROMPT			"\e[32mminishell > \e[0m"
# define BACK_CURSOR			"\033[2D"
# define CLEAR_FROM_CURSOR		"\033[0K"

# define STATUS_SYNTAX_ERROR		258
# define STATUS_TOKEN_ERROR			2
# define STATUS_CMD_NOT_FOUND		127
# define STATUS_CMD_NOT_EXECUTABLE	126

#endif
