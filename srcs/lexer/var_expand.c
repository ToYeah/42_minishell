/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_expand.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: totaisei <totaisei@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/15 17:19:26 by totaisei          #+#    #+#             */
/*   Updated: 2021/02/16 14:18:28 by totaisei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "utils.h"

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
	size_t val_len;

	val_len = 0;
	while (ft_isalnum(str[val_len]) || str[val_len] == '_')
		val_len++;
	return (val_len);
}

char			*extract_val_name(char *str)
{
	size_t	val_len;
	char	*res;

	if (*str == '?')
		return (ft_strdup("?"));
	val_len = calc_val_len(str);
	if (!(res = malloc(sizeof(char) * val_len + 1)))
		return (NULL);
	ft_strlcpy(res, str, val_len + 1);
	return (res);
}

char			*expansion_var_esc(char *str,  t_token_state state)
{
	char *res;
	size_t res_index;
	size_t index;
	char *esc_chars;

	esc_chars = "\'\"\\$";
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
	res = malloc(sizeof(char *) * (res_index + 1));//error
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

char			*expansion(char *str, size_t *index, t_token_state state)
{
	char *var_name;
	char *value;
	char *tmp;
	char *res;
	extern t_env *g_envs;

	str[*index] = '\0';
	if (!(var_name = extract_val_name(&str[*index + 1])))
		error_exit();
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

char			*envarg_expansion(char *str)
{
	size_t i;
	t_token_state state;
	t_token_type type;
	char *editable_str;

	editable_str = ft_strdup(str);
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
		if (type == CHAR_ESCAPESEQUENCE && ft_strchr("\'\"$", editable_str[i + 1]) != NULL)
		{
			if(!editable_str[i + 1])
				return editable_str;
			i += 2;
			continue;
		}
		state = judge_token_state(state, type);
		if (editable_str[i] == '$' && editable_str[i + 1]
		&& (state == STATE_GENERAL || state == STATE_IN_DQUOTE))
			editable_str = expansion(editable_str, &i, state);
		i++;
	}
	return (editable_str);
}
