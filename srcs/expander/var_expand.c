/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_expand.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: totaisei <totaisei@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/15 17:19:26 by totaisei          #+#    #+#             */
/*   Updated: 2021/02/21 10:03:45 by totaisei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "utils.h"
#include "token.h"

void	shift_quote(char *quote_start, char *end, t_tokeniser *toker)
{
	size_t	i;
	char	*cpy_start;

	i = 0;
	cpy_start = quote_start + 1;
	while (&cpy_start[i] != end)
	{
		quote_start[i] = cpy_start[i];
		i++;
	}
	toker->tok_i -= 2;
}


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

char			*expansion(char *str, size_t *index, t_token_state state)
{
	char *var_name;
	char *value;
	char *tmp;
	char *res;
	extern t_env *g_envs;

	if (!(var_name = extract_var_name(&str[*index + 1])))
		error_exit();
	if(ft_strlen(var_name) == 0)
		return str;
	str[*index] = '\0';
	if(!(value = expansion_var_esc(search_env(g_envs, var_name), state)))
		error_exit();
	if(!(tmp = ft_strjoin(str, value)))
		error_exit();
	if(!(res = ft_strjoin(tmp, &str[*index + ft_strlen(var_name) + 1])))
		error_exit();
	*index = ft_strlen(tmp) - 1;
	free(value);
	free(var_name);
	free(tmp);
	free(str);
	return res;
}

char			*envvar_expansion(char *str)
{
	size_t i;
	t_token_state state;
	t_token_type type;
	char *editable_str;

	if (!str)
		return (NULL);
	editable_str = ft_strdup(str);//error
	i = 0;
	state = STATE_GENERAL;
	while (editable_str[i] != '\0')
	{
		if (ft_strchr("\'\"\\$", editable_str[i]) == NULL)
		{
			i++;
			continue;
		}
		type = judge_token_type(editable_str[i]);
		if (type == CHAR_ESCAPE && ft_strchr("\'\"$", editable_str[i + 1]) != NULL)
		{
			if(!editable_str[i + 1])
				return editable_str;
			i += 2;
			continue;
		}
		state = judge_token_state(state, type);
		if (editable_str[i] == '$' )
		{
			if (state == STATE_GENERAL || state == STATE_IN_DQUOTE)
				editable_str = expansion(editable_str, &i, state);
		}
		i++;
	}
	return (editable_str);
}


void *expande_tokens(t_token **tokens)
{
	t_token *now_token;
	t_token *last_token;
	t_token *res_tokens;
	t_token *expanded_token;
	char *expanded_str;

	if (!tokens || !*tokens)
		return (NULL);
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