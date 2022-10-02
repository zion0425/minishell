/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yjoo <yjoo@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 20:20:41 by yjoo              #+#    #+#             */
/*   Updated: 2022/10/02 23:30:31 by yjoo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	merge_token(char *line, int *idx, t_token *new_token)
{
	char	*tmp;
	t_token	*join_token;

	(*idx)++;
	join_token = (t_token *)ft_calloc(1, sizeof(t_token));
	input_token(join_token, line, idx);
	tmp = new_token->token;
	new_token->token = ft_strjoin(new_token->token, join_token->token);
	free(join_token->token);
	free(join_token);
	free(tmp);
}

char	*dollar_token_handle(char *line, int *idx, t_token *new)
{
	int		start;
	char	*ret;

	(*idx)++;
	start = *idx;
	while (line[*idx] && !is_whitespace(line[*idx]))
	{
		if (get_token_type(line, *idx) != WORD)
			break ;
		(*idx)++;
	}
	if (start == *idx)
	{
		ret = ft_strdup("");
		new->type = WORD;
	}
	else
		ret = ft_substr(line, start, *idx - start);
	if (!ret)
		return (NULL);
	(*idx)--;
	return (ret);
}

t_token	*search_token(t_token *head, int type)
{
	t_token	*ret;

	ret = head;
	while (ret->next)
	{
		if (ret->type == type)
			return (ret);
		ret = ret->next;
	}
	return (ret);
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

void	free_token_list(t_token *head_token, char *line)
{
	t_token	*tmp;

	tmp = head_token;
	while (tmp)
	{
		head_token = head_token->next;
		free(tmp->token);
		free(tmp);
		tmp = head_token;
	}
	if (line)
		free(line);
}
