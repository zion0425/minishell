/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yjoo <yjoo@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 23:16:32 by yjoo              #+#    #+#             */
/*   Updated: 2022/09/22 23:27:58 by yjoo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*dollar_token_handle(char *line, int *idx)
{
	int		start;
	char	*ret;

	(*idx)++;
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
		free(tmp);
		tmp = head_token;
	}
}

//삭제예정
void	show_token_list(t_token *head_token)
{
	t_token	*cur_token;
	int		i;

	cur_token = head_token;
	i = 1;
	if (!head_token)
		return ;
	while (1)
	{
		printf("cur[%d]token : %d, %s\n", i, cur_token->type, cur_token->token);
		if (!cur_token->next)
			break ;
		cur_token = cur_token->next;
		i++;
	}
}
