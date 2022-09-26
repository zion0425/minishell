/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yjoo <yjoo@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 23:16:32 by yjoo              #+#    #+#             */
/*   Updated: 2022/09/26 13:46:20 by yjoo             ###   ########.fr       */
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

char	*check_envp(char *str, int idx)
{
	char	*ret;
	char	**envp_split;

	envp_split = ft_split(g_envp[idx], '=');
	if (ft_strlen(str) == ft_strlen(envp_split[0]))
	{
		ret = ft_strdup(envp_split[1]);
		free_split(envp_split);
		return (ret);
	}
	else
	{
		free_split(envp_split);
		return (NULL);
	}
}

char	*find_value(char *key)
{
	int		idx;
	char	*ret;
	char	**split;

	idx = -1;
	while (g_envp[++idx])
	{
		if (ft_strncmp(g_envp[idx], key, ft_strlen(key)) == 0)
		{
			split = ft_split(g_envp[idx], '=');
			if (ft_strlen(split[0]) == ft_strlen(key))
			{
				ret = ft_strdup(split[1]);
				free(key);
				free_split(split);
				return (ret);
			}
			else
				free_split(split);
		}
	}
	free(key);
	ret = ft_strdup("");
	return (ret);
}

void	dollar_to_word(t_token *head_token, int type, char *tmp)
{
	int		idx;
	char	*value;
	t_token	*cur;

	cur = serach_token(head_token, type);
	idx = -1;
	if (cur->type == type)
	{
		while (cur->token[++idx])
		{
			if (cur->token[idx + 1] == '=')
			{
				idx++;
				tmp = ft_substr(cur->token, idx, ft_strlen(cur->token) - idx);
				break ;
			}
		}
		if (cur->token[idx] == '\0')
			tmp = ft_strdup("");
		value = find_value(ft_substr(cur->token, 0, idx));
		free(cur->token);
		cur->token = ft_strjoin(value, tmp);
		free(tmp);
		free(value);
	}
}

void	dquote_dollar_to_word(t_token *head_token)
{
	int		idx;
	t_token	*cur;

	cur = serach_token(head_token, DQUOTE);
	idx = -1;
	while (cur->token[++idx])
	{
		if (cur->token[idx] == '$')
		{
			idx++;
			dollar_to_word(cur, DQUOTE, NULL);
		}
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
