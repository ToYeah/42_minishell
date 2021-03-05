/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: totaisei <totaisei@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/12 20:07:55 by nfukada           #+#    #+#             */
/*   Updated: 2021/03/05 11:32:00 by totaisei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

# include "libft.h"

int		is_builtin(char **args);
int		exec_echo(char **args);
int		exec_exit(char **args);
int		exec_builtin(char **args);
int		exec_cd(char **args);
int		exec_pwd(char **args);
void	bind_pwd_valie(void);

#endif
