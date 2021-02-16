/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_debug.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: totaisei <totaisei@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/15 18:01:20 by totaisei          #+#    #+#             */
/*   Updated: 2021/02/16 19:41:20 by totaisei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "lexer.h"
#include "stdio.h"
#include "utils.h"

t_env *g_envs;

void	print_tokens_detail(t_token *token)
{
	t_token *now;

	if(!token)
		return;
	now = token;
		printf("////////////////////////////\n");
	while(now)
	{
		printf("token_type : %d\n",now->type);
		printf("token_str : %s\n",now->data);
		now = now->next;
		printf("////////////////////////////\n");
	}
}

void	print_tokens_line(t_token *token)
{
	t_token *now;
	if(!token)
		return;
	now = token;
	while(now)
	{
		if(now != token)
			printf(" -> ");
		if(now->type == TOKEN)
			printf("[%s]",now->data);
		else
			printf("{%s}",now->data);
		now = now->next;
	}
	printf("\n");
}


int				main()
{
	char *line;
	int res;
	char *res_line;
	t_token *tokens;

	g_envs = create_envs_from_environ();
	res = 1;
	while (res)
	{
		res = ft_get_next_line(0, &line);
		res_line = envarg_expansion(line);
		tokens = tokenise(res_line);
		//printf("\nexpanded :\n%s\n",res_line);
		//print_tokens_detail(tokens);
		printf("\ntokenised :\n");
		print_tokens_line(tokens);
		free(line);
		free(res_line);
		del_token_list(&tokens);
	}
	
	// printf("input: %s\n", str);
	// envarg_expansion(str);
}
