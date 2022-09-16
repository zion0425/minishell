/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yjoo <yjoo@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/11 13:41:15 by yjoo              #+#    #+#             */
/*   Updated: 2022/09/16 21:07:03 by yjoo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	prompt(char **line)
{
	*line = readline("minishell$> ");
	if (*line == NULL)
	{	
		ft_putstr_fd("\x1b[1A\033[12Cexit\n", STDOUT_FILENO);
		exit(EXIT_SUCCESS);
	}
}

int	get_token_type(char *line, int idx)
{
	if (line[idx] == '<')
	{
		if (line[idx + 1] && line[idx + 1] == '<')
			return (HEREDOC);
		return (REDIRIN);
	}
	else if (line[idx] == '>')
	{
		if (line[idx + 1] && line[idx + 1] == '>')
			return (APPEND);
		return (REDIROUT);
	}
	else if (line[idx] == '|')
		return (PIPE);
	else if (line[idx] == '\'')
		return (QUOTE);
	else if (line[idx] == '"')
		return (DQUOTE);
	else if (line[idx] == '$')
		return (DOLLAR);
	return (WORD);
}

char	*quote_token_handle(char *line, int *idx)
{
	int		quote_cnt;
	int		start;
	char	quote_type;
	char	*ret;

	quote_type = line[*idx];
	start = (*idx) + 1;
	quote_cnt = -2;
	while (line[*idx])
	{
		if (line[*idx] == quote_type)
			quote_cnt++;
		if (quote_cnt == 0)
			break ;
		(*idx)++;
	}
	if (quote_cnt == 0)
	{
		ret = ft_substr(line, start, *idx - start);
		return (ret);
	}
	return (NULL);
}

char	*word_token_handle(char *line, int *idx)
{
	int		start;
	char	*ret;

	start = *idx;
	(void)ret;
	while (line[*idx] && !(line[*idx] == ' ' || \
		(line[*idx] >= 9 && line[*idx] <= 13)))
		(*idx)++;
	ret = ft_substr(line, start, *idx - start);
	if (!ret)
		return (NULL);
	return (ret);
}

void	input_token(t_token *new_token, char *line, int *idx)
{
	if (new_token->type == HEREDOC || new_token->type == APPEND)
	{
		if (new_token->type == HEREDOC)
			new_token->token = ft_strdup("<<");
		else if (new_token->type == APPEND)
			new_token->token = ft_strdup(">>");
		(*idx)++;
	}
	else if (new_token->type == REDIRIN)
		new_token->token = ft_strdup("<");
	else if (new_token->type == REDIRIN)
		new_token->token = ft_strdup("<");
	else if (new_token->type == REDIROUT)
		new_token->token = ft_strdup(">");
	else if (new_token->type == PIPE)
		new_token->token = ft_strdup("|");
	else if (new_token->type == DOLLAR)
		new_token->token = ft_strdup("$");
	else if (new_token->type == QUOTE || new_token->type == DQUOTE)
		new_token->token = quote_token_handle(line, idx);
	else if (new_token->type == WORD)
		new_token->token = word_token_handle(line, idx);
}

int	add_token_list(t_token **head_token, t_token **new_token)
{
	t_token	*cur_token;

	if (*new_token == NULL)
		return (0);
	if (*head_token == NULL)
		*head_token = *new_token;
	else
	{
		cur_token = *head_token;
		while (cur_token->next != NULL)
			cur_token = cur_token->next;
		cur_token->next = *new_token;
		(*new_token)->prev = cur_token;
	}
	return (1);
}

int	new_token(t_token **head_token, char *line, int *idx)
{
	t_token	*new_token;

	new_token = (t_token *)ft_calloc(sizeof(t_token), 1);
	if (!new_token)
		return (0);
	new_token->type = get_token_type(line, *idx);
	input_token(new_token, line, idx);
	if (!new_token->token)
	{
		free(new_token);
		return (0);
	}
	return (add_token_list(head_token, &new_token));
}

int	create_token_list(char *line, t_token **head_token)
{
	int	idx;

	idx = 0;
	while (line[idx])
	{
		while (line[idx] && (line[idx] == ' ' || \
		(line[idx] >= 9 && line[idx] <= 13)))
			idx++;
		if (!line[idx])
			return (0);
		if (!new_token(head_token, line, &idx))
			return (0);
		idx++;
	}
	return (1);
}

int	parse(void)
{
	char	*line;
	t_token	*head_token;

	prompt(&line);
	if (is_empty(line))
	{
		free(line);
		return (0);
	}
	if (!create_token_list(line, &head_token))
		return (0);
	add_history(line);
	free(line);
	return (1);
}
