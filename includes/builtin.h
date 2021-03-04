/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfukada <nfukada@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/12 20:07:55 by nfukada           #+#    #+#             */
/*   Updated: 2021/03/04 14:59:45 by nfukada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

# include "libft.h"

int		is_builtin(char **args);
int		exec_echo(char **args);
int		exec_exit(char **args);
int		exec_builtin(char **args);

#endif
