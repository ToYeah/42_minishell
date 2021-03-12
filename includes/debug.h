/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfukada <nfukada@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/12 12:43:13 by nfukada           #+#    #+#             */
/*   Updated: 2021/03/12 12:43:40 by nfukada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEBUG_H
# define DEBUG_H

# ifndef DEBUG
#  define DEBUG			0
# endif
# ifndef LEAKS
#  define LEAKS			0
# endif

# if LEAKS

void			end(void) __attribute__((destructor));

# endif

#endif
