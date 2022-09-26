/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yjoo <yjoo@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 20:20:41 by yjoo              #+#    #+#             */
/*   Updated: 2022/09/26 13:53:26 by yjoo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	is_empty(char *line)
{
	int	idx;

	idx = -1;
	while (line[++idx])
	{
		if (line[idx] != ' ' && !(line[idx] >= 9 && line[idx] <= 13))
			return (0);
	}
	return (1);
}

t_token	*serach_token(t_token *head, int type)
{
	t_token	*ret;

	ret = head;
	while (ret->next)
	{
		if (ret->type == type)
			return (ret);
		ret = ret->next;
	}
	ret = head;
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

void	free_token_list(t_token *head_token)
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
}
