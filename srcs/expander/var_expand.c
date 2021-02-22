/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_expand.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: totaisei <totaisei@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/15 17:19:26 by totaisei          #+#    #+#             */
/*   Updated: 2021/02/22 10:34:37 by totaisei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"
#include "lexer.h"
#include "utils.h"

#define VAR_NAME 0
#define VALUE 1
#define TMP 2
#define RES 3


t_token_state	judge_token_state(t_token_state state, t_token_type type)
{
	if (state == STATE_GENERAL)
	{
		if (type == CHAR_DQUOTE)
			return (STATE_IN_DQUOTE);
		if (type == CHAR_QOUTE)
			return (STATE_IN_QUOTE);
	}
	else if (state == STATE_IN_DQUOTE && type != CHAR_DQUOTE)
		return (STATE_IN_DQUOTE);
	else if (state == STATE_IN_QUOTE && type != CHAR_QOUTE)
		return (STATE_IN_QUOTE);
	return (STATE_GENERAL);
}

size_t			calc_val_len(char *str)
{
	size_t var_len;

	var_len = 0;
	while (ft_isalnum(str[var_len]) || str[var_len] == '_')
		var_len++;
	return (var_len);
}

char			*extract_var_name(char *str)
{
	size_t	var_len;
	char	*res;

	if (*str == '?')
		return (ft_strdup("?"));
	var_len = calc_val_len(str);
	if (!(res = malloc(sizeof(char) * var_len + 1)))
		return (NULL);
	ft_strlcpy(res, str, var_len + 1);
	return (res);
}

char			*expansion_var_esc(const char *str,  t_token_state state)
{
	char *res;
	size_t res_index;
	size_t index;
	char *esc_chars;

	esc_chars = "\"\\$";
	if(state == STATE_GENERAL)
		esc_chars = "\'\"\\$|;><";
	res_index = 0;
	index = 0;
	while(str[index] != 0)
	{
		if (ft_strchr(esc_chars, str[index]) != NULL)
			res_index++;
		res_index++;
		index++;
	}
	if(!(res = malloc(sizeof(char *) * (res_index + 1))))
		error_exit();
	index = 0;
	res_index = 0;
	while(str[index] != 0)
	{
		if (ft_strchr(esc_chars, str[index]) != NULL)// escape?
		{
			res[res_index] = '\\';
			res_index++;
		}
		res[res_index] = str[index];
		res_index++;
		index++;
	}
	res[res_index] = '\0';
	return res;
}

#include <stdio.h>

void		expansion(t_expander *exper)
{
	char *vars[4];
	extern t_env *g_envs;

	if (!(vars[VAR_NAME] =
		extract_var_name(&exper->str[exper->str_i + 1])))
		error_exit();
	if(ft_strlen(vars[VAR_NAME]) == 0)
		return ;
	exper->str[exper->str_i] = '\0';
	if(!(vars[VALUE] =
		expansion_var_esc(
			search_env(g_envs, vars[VAR_NAME]), exper->state)))
		error_exit();
	if(!(vars[TMP] = ft_strjoin(exper->str, vars[VALUE])))
		error_exit();
	if(!(vars[RES] = ft_strjoin(vars[TMP],
		&exper->str[exper->str_i + ft_strlen(vars[VAR_NAME]) + 1])))
		error_exit();
	exper->str_i = ft_strlen(vars[TMP]) - 1;
	free(vars[VALUE]);
	free(vars[VAR_NAME]);
	free(vars[TMP]);
	free(exper->str);
	exper->str = vars[RES];
}

char			*envvar_expansion(char *input)
{
	t_expander exper;

	if (!input)
		return (NULL);
	expander_init(&exper, input);
	while (exper.str[exper.str_i] != '\0')
	{
		exper.type = judge_token_type(exper.str[exper.str_i]);
		exper.state = judge_token_state(exper.state, exper.type);
		if (exper.type == CHAR_ESCAPE &&
			ft_strchr("\'\"$", exper.str[exper.str_i + 1]) != NULL)
		{
			if (exper.str[exper.str_i + 1] == '\0')
				return (exper.str);
			exper.str_i++;
		}
		else if (exper.str[exper.str_i] == '$' &&
			(exper.state == STATE_GENERAL || exper.state == STATE_IN_DQUOTE))
		{
			expansion(&exper);
		}
		exper.str_i++;
	}
	return (exper.str);
}

void expande_tokens(t_token **tokens)
{
	t_token *now_token;
	t_token *last_token;
	t_token *res_tokens;
	t_token *expanded_token;
	char *expanded_str;

	if (!tokens || !*tokens)
		return ;
	last_token = NULL;
	res_tokens = NULL;
	now_token = *tokens;
	while (now_token != NULL)
	{
		expanded_str = envvar_expansion(now_token->data);
		expanded_token = tokenise(expanded_str, TRUE);
		free(expanded_str);
		if (res_tokens == NULL)
			res_tokens = expanded_token;
		token_join(last_token, expanded_token);
		printf("%s\n",find_last_token(expanded_token)->data);
		last_token = find_last_token(expanded_token);
		now_token = now_token->next;
	}
	del_token_list(tokens);
	*tokens = res_tokens;
}