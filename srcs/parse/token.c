/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yjoo <yjoo@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/17 12:09:42 by yjoo              #+#    #+#             */
/*   Updated: 2022/09/22 23:21:13 by yjoo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	add_token_list(t_token **head_token, t_token **new_token)
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

static char	*word_token_handle(char *line, int *idx)
{
	int		start;
	char	*ret;

	start = *idx;
	while (line[*idx] && !(line[*idx] == ' ' || \
		(line[*idx] >= 9 && line[*idx] <= 13)))
	{
		if (get_token_type(line, *idx) != WORD)
			break ;
		(*idx)++;
	}
	ret = ft_substr(line, start, *idx - start);
	if (!ret)
		return (NULL);
	(*idx)--;
	return (ret);
}

static char	*quote_token_handle(char *line, int *idx)
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

static void	input_token(t_token *new_token, char *line, int *idx)
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
		new_token->token = dollar_token_handle(line, idx);
	else if (new_token->type == QUOTE || new_token->type == DQUOTE)
		new_token->token = quote_token_handle(line, idx);
	else if (new_token->type == WORD)
		new_token->token = word_token_handle(line, idx);
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
