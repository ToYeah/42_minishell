/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: totaisei <totaisei@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/12 17:00:52 by totaisei          #+#    #+#             */
/*   Updated: 2021/02/15 12:29:57 by totaisei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "stdio.h"
#include "utils.h"

t_env *g_envs;


char *search_env(t_env **envs, char *name)
{
	t_env	*now;

	now = *envs;
	while (now)
	{
		if (ft_strncmp(now->name, name, ft_strlen(name) + 1) == 0)
			return (now->value);
		now = now->next;
	}
	return ("");
}


void	del_token(t_token **token_p)
{
	t_token *token;

	if(!token_p || !*token_p)
		return ;
	token = *token_p;
	if(token->data)
		free(token->data);
	if(token->next)
		token->next->prev = token->prev;
	if(token->prev)
		token->prev->next = token->next;
	free(token);
	*token_p = NULL;
}

void	del_token_list(t_token *token)
{
	t_token *now;
	t_token *tmp;

	now = token;
	while(now)
	{
		tmp = now->next;
		del_token(&now);
		now = tmp;
	}
}


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

t_token *token_init(size_t len, t_token *prev)
{
	t_token *res;

	if (!(res = malloc(sizeof(t_token))))
		return (NULL);
	if(!(res->data = malloc(sizeof(char) * (len + 1))))
		return (NULL);
	res->data[0] = '\0';
	res->type = CHAR_NULL;
	res->next = NULL;
	res->prev = prev;
	return (res);
}

void token_add_front(t_tokeniser *toker)
{
	t_token *tmp_token;
	if(toker->tok_i > 0)
	{
		toker->token->data[toker->tok_i] = '\0';
		tmp_token = token_init(toker->str_len - toker->str_i, toker->token);//error
		toker->token->next = tmp_token;
		toker->token = tmp_token;
		toker->tok_i = 0;
	}
}

void general_state_sep(t_tokeniser *toker, t_token_type type, char *str)
{
	token_add_front(toker);//error
	if(type != CHAR_WHITESPACE)
	{
		toker->token->data[toker->tok_i++] = str[toker->str_i];
		toker->token->type = type;
		token_add_front(toker); //error
	}
}

void general_state(t_tokeniser *toker, t_token_type type, char *str)
{
	if(type == '\'' || type == '\"' || type == '\\' || type == CHAR_GENERAL)
	{
		if(type == CHAR_ESCAPESEQUENCE && str[toker->str_i + 1] != '\0')
			toker->token->data[toker->tok_i++] = str[++toker->str_i];
		else
			toker->token->data[toker->tok_i++] = str[toker->str_i];
		if(type == '\'')
			toker->state = STATE_IN_QUOTE;
		else if(type == '\"')
			toker->state = STATE_IN_DQUOTE;
		else
			toker->state = STATE_GENERAL;
	}
	else
		general_state_sep(toker, type, str);
	return ;
}

void quote_state(t_tokeniser *toker, t_token_type type, char *str)
{
	(void)type;
	toker->token->data[toker->tok_i++] = str[toker->str_i];
	if(str[toker->str_i] == CHAR_QOUTE)
		toker->state = STATE_GENERAL;
}


void d_quote_state(t_tokeniser *toker, t_token_type type, char *str)
{
	if(type == CHAR_ESCAPESEQUENCE && str[toker->str_i + 1] != '\0')
		toker->token->data[toker->tok_i++] = str[++toker->str_i];
	else
	{
		toker->token->data[toker->tok_i++] = str[toker->str_i];
		if( str[toker->str_i] == CHAR_DQUOTE)
			toker->state = STATE_GENERAL;
	}
}

void close_token_list(t_token *last_token, size_t token_index)
{
	if(token_index == 0)
		del_token(&last_token);
	else
		last_token->data[token_index] = '\0';
}

void tokenise_input(char *str,t_token *start_token, size_t len)
{
	t_tokeniser toker;
	t_token_type type;

	toker.token = start_token;
	toker.state = STATE_GENERAL;
	toker.str_i = 0;
	toker.tok_i = 0;
	toker.str_len = len;
	while (str[toker.str_i] != '\0')
	{
		type = judge_token_type(str[toker.str_i]);
		if(toker.state == STATE_GENERAL)
			general_state(&toker, type, str);
		else if(toker.state == STATE_IN_QUOTE)
			quote_state(&toker, type, str);
		else if(toker.state == STATE_IN_DQUOTE)
			d_quote_state(&toker, type, str);
		toker.str_i++;
	}
	close_token_list(toker.token, toker.tok_i);
}

void tokenise(char *input)
{
	size_t		input_len;
	t_token		*start_token;

	input_len = ft_strlen(input);
	start_token = token_init(input_len, NULL);
	tokenise_input(input, start_token, input_len);
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
	char *env_value;
	char *expanded_var;
	char *tmp;
	char *res;

	str[*index] = '\0';
	var_name = extract_val_name(&str[*index + 1]);//error
	//printf("var_name:%s\n",var_name);
	env_value = search_env(&g_envs, var_name);
	expanded_var = ft_strdup(env_value);//error
	tmp = ft_strjoin(str, expanded_var);//error
	res = ft_strjoin(tmp, &str[*index + ft_strlen(var_name) + 1]);//error
	//printf("%s\n",res);
	*index = ft_strlen(tmp) - 1;
	free(expanded_var);
	free(var_name);
	free(tmp);
	free(str);
	return res;
}

char	*envarg_expansion(char *str)
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
		//printf("%c\n",str[i]);
		//printf("state:%d\n",state);
		if(ft_strchr("\'\"\\$",editable_str[i]) == NULL)
		{
			i++;
			continue;
		}
		type = judge_token_type(editable_str[i]);
		if(type == CHAR_ESCAPESEQUENCE && ft_strchr("\'\"$",editable_str[i+1]) != NULL)
		{
			i += 2;
			continue;
		}
		state = judge_token_state(state, type);
		if(editable_str[i] == '$' && editable_str[i + 1] && (state == STATE_GENERAL || state == STATE_IN_DQUOTE))
			editable_str = expansion(editable_str, &i);
		i++;
	}
	return (editable_str);
}

void	print_tokens_detail(t_token *token)
{
	t_token *now;
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
	now = token;
	while(now)
	{
		if(now != token)
			printf(" -> ");
		printf("%s",now->data);
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
	size_t len;

	g_envs = create_envs_from_environ();
	res = 1;
	while (res)
	{
		res = ft_get_next_line(0, &line);
		res_line = envarg_expansion(line);
		len = ft_strlen(res_line);
		tokens = token_init(len, NULL);
		tokenise_input(res_line, tokens, len);
		printf("\nexpanded :\n%s\n",res_line);
		//print_tokens_detail(tokens);
		printf("\ntoknised :\n");
		print_tokens_line(tokens);
		free(line);
		free(res_line);
		del_token_list(tokens);
	}
	
	// printf("input: %s\n", str);
	// envarg_expansion(str);
}
