/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: totaisei <totaisei@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/12 20:07:55 by nfukada           #+#    #+#             */
/*   Updated: 2021/02/27 15:07:25 by totaisei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

#include "libft.h"

int		is_builtin(char **args);
int		exec_echo(char **args, t_bool pipe_flag);
void	exec_builtin(char **args);

#endif
