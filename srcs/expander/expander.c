/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: totaisei <totaisei@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/22 12:11:37 by totaisei          #+#    #+#             */
/*   Updated: 2021/03/12 15:19:02 by totaisei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"
#include "utils.h"
#include "libft.h"

#define VAR_NAME 0
#define VALUE 1
#define TMP 2
#define RES 3

void			expander_init(t_expander *exper, char *input)
{
	exper->str = ft_strdup(input);
	if (exper->str == NULL)
		error_exit(NULL);
	exper->str_i = 0;
	exper->state = STATE_GENERAL;
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

char			*extract_var_name(char *str)
{
	size_t	var_len;
	char	*res;

	if (*str == '?')
		return (ft_strdup("?"));
	var_len = 0;
	while (ft_isalnum(str[var_len]) || str[var_len] == '_')
		var_len++;
	if (!(res = malloc(sizeof(char) * var_len + 1)))
		error_exit(NULL);
	ft_strlcpy(res, str, var_len + 1);
	return (res);
}

void			expand_var_in_str(t_expander *exper)
{
	char			*vars[4];
	char			*env_value;
	size_t			after_var_index;

	if (!(vars[VAR_NAME] = extract_var_name(&exper->str[exper->str_i + 1])))
		error_exit(NULL);
	if (ft_strlen(vars[VAR_NAME]) == 0)
		return ;
	exper->str[exper->str_i] = '\0';
	env_value = dup_env_value(vars[VAR_NAME]);
	after_var_index = exper->str_i + ft_strlen(vars[VAR_NAME]) + 1;
	if (!(vars[VALUE] = create_expanded_str(env_value, exper->state, FALSE)) ||
		!(vars[TMP] = ft_strjoin(exper->str, vars[VALUE])) ||
		!(vars[RES] = ft_strjoin(vars[TMP], &exper->str[after_var_index])))
	{
		error_exit(NULL);
	}
	exper->str_i = ft_strlen(vars[TMP]) - 1;
	free(vars[VALUE]);
	free(vars[VAR_NAME]);
	free(vars[TMP]);
	free(env_value);
	free(exper->str);
	exper->str = vars[RES];
}

char			*expand_env_var(char *input)
{
	t_expander exper;

	if (!input)
		return (NULL);
	expander_init(&exper, input);
	while (exper.str[exper.str_i] != '\0')
	{
		exper.type = judge_token_type(exper.str[exper.str_i]);
		exper.state = judge_token_state(exper.state, exper.type);
		if (exper.type == CHAR_ESCAPE && exper.str[exper.str_i + 1] != '\0' &&
			ft_strchr("\\\'\"$", exper.str[exper.str_i + 1]) != NULL)
		{
			exper.str_i++;
		}
		else if (exper.str[exper.str_i] == '$' &&
			(exper.state == STATE_GENERAL || exper.state == STATE_IN_DQUOTE))
		{
			expand_var_in_str(&exper);
		}
		exper.str_i++;
	}
	return (exper.str);
}
