/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: totaisei <totaisei@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/12 17:00:52 by totaisei          #+#    #+#             */
/*   Updated: 2021/02/13 17:31:24 by totaisei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "stdio.h"

t_token_type	judge_token_type(char c)
{
	int			command_count;
	const char	commands[] = {
		'|', '&', '\'', '\"', ' ', ';', '\\', '\t', '\n', '>', '<', '\0'
	};

	command_count = 12;
	while (command_count--)
	{
		if (commands[command_count] == c)
			return (commands[command_count]);
	}
	return (CHAR_GENERAL);
}

t_token *token_init(size_t len)
{
	t_token *res;

	if (!(res = malloc(sizeof(t_token))))
		return (NULL);
	if(!(res->data = malloc(sizeof(char) * (len + 1))))
		return (NULL);
	res->data[0] = '\0';
	res->type = CHAR_NULL;
	res->next = NULL;
}

void general_state(t_token* token, t_token_state state, t_token_type type, char c)
{
	
}

int a(char *str, size_t len)
{
	size_t i;
	size_t j;
	t_token *token;
	t_token_type type;
	t_token_state state;

	token = token_init(len);// error
	state = STATE_GENERAL;
	i = 0;
	while (str[i] != '\0')
	{
		type = judge_token_type(str[i]);
		
	}
	
}

t_token_list tokenise(char *input)
{
	t_token_list	*tokens;
	size_t			input_len;

	if(!(tokens = malloc(sizeof(t_token_list))))
		exit(EXIT_FAILURE); //TODO error
	input_len = ft_strlen(input);

}

//environ

t_token_state judge_token_state(t_token_state state, t_token_type type)
{
	if(state == STATE_GENERAL)
	{
		if(type == CHAR_DQUOTE)
			return (STATE_IN_DQUOTE);
		if(type == CHAR_QOUTE)
			return (STATE_IN_QUOTE);
	}
	else if(state == STATE_IN_DQUOTE && type != CHAR_DQUOTE)
			return (STATE_IN_DQUOTE);
	else if(state == STATE_IN_QUOTE && type != CHAR_QOUTE)
			return (STATE_IN_QUOTE);
	else
		return (STATE_GENERAL);
}

size_t calc_val_len(char *str)
{
	size_t val_len;

	val_len = 0;
	while (ft_isalnum(str[val_len]) || str[val_len] == '_')
		val_len++;
	return (val_len);
}

char *extract_val_name(char *str)
{
	size_t val_len;
	char *res;

	if(*str == '?')
		return ft_strdup("?");
	val_len = calc_val_len(str);
	if(!(res = malloc(sizeof(char) * val_len + 1)))
		return NULL;
	ft_strlcpy(res, str, val_len + 1);
	return res;
}

char *expansion(char *str, size_t *index)
{
	char *var_name;
	char *expanded_var;
	char *tmp;
	char *res;

	str[*index] = '\0';
	var_name = extract_val_name(&str[*index + 1]);//error
	printf("var_name:%s\n",var_name);
	expanded_var = "HELLO WORLD"; //find_environment variable
	tmp = ft_strjoin(str, expanded_var);//error
	res = ft_strjoin(tmp, &str[*index + ft_strlen(var_name) + 1]);//error
	//printf("%s\n",res);
	*index = ft_strlen(tmp);
	free(var_name);
	free(tmp);
	return res;
}

void	envarg_expansion(char *str)
{
	size_t i;
	t_token_state state;
	t_token_type type;

	i = 0;
	state = STATE_GENERAL;
	while (str[i] != '\0')
	{
		//printf("state:%d\n",state);
		if(ft_strchr("\'\"\\$",str[i]) == NULL)
		{
			i++;
			continue;
		}
		type = judge_token_type(str[i]);
		if(type == CHAR_ESCAPESEQUENCE && ft_strchr("\'\"$",str[i+1]) != NULL)
		{
			i += 2;
			continue;
		}
		state = judge_token_state(state, type);
		if(str[i] == '$' && str[i + 1]
		&& (state == STATE_GENERAL || state == STATE_IN_DQUOTE))
			str = expansion(str, &i);
		i++;
	}
	printf("%s\n",str);
}

int				main()
{
	char *line;
	int res;

	res = 1;
	while (res)
	{
		ft_get_next_line(0, &line);
		envarg_expansion(line);
		free(line);
	}
	
	// printf("input: %s\n", str);
	// envarg_expansion(str);
}
