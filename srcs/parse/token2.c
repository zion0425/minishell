/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yjoo <yjoo@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 23:16:32 by yjoo              #+#    #+#             */
/*   Updated: 2022/09/27 14:40:20 by yjoo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*find_value(char *key)
{
	int		idx;
	char	*ret;
	char	**split;

	idx = -1;
	while (g_var.envp[++idx])
	{
		if (ft_strncmp(g_var.envp[idx], key, ft_strlen(key)) == 0)
		{
			split = ft_split(g_var.envp[idx], '=');
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

char	*reassembly_str(char *cur, char *tmp, int idx)
{
	char	*ret;
	char	*value;

	if (ft_strlen(cur) == 1 && cur[0] == '?')
		ret = ft_itoa(g_var.exit_code);
	else
	{
		while (cur[++idx])
		{
			if (!ft_isalnum(cur[idx]))
			{
				tmp = ft_substr(cur, idx, ft_strlen(cur) - idx);
				break ;
			}
		}
		if (!tmp && cur[idx] == '\0')
			tmp = ft_strdup("");
		value = find_value(ft_substr(cur, 0, idx));
		ret = ft_strjoin(value, tmp);
		free(tmp);
		free(value);
	}
	free(cur);
	return (ret);
}

char	*dquote_dollar(char *cur, int *idx)
{
	int		start;
	char	*tmp;
	char	*ret;

	start = *idx;
	while (cur[*idx] && ft_isalnum(cur[*idx]) && !is_whitespace(cur[*idx]))
		(*idx)++;
	tmp = ft_strsub(cur, start, (*idx) - start);
	if (tmp[0] != '\0');
		ret = reassembly_str(tmp, NULL, -1);
	else
		
}

char	*check_dquote(char *cur)
{
	int		idx;
	char	*ret;

	idx = -1;
	if (ft_strlen(cur) == 0)
		return (cur);
	ret = ft_strdup("");
	while (cur[++idx])
	{
		if (cur[idx] == '$')
		{
			idx++;
			dquote_dollar(cur, &idx);
		}
	}
	return (ret);
}

int	envp_convert(t_token *head, int cnt)
{
	int		idx;
	t_token	*cur;

	idx = -1;
	cur = head;
	while (++idx < cnt)
	{
		if (cur->type == DOLLAR)
			cur->token = reassembly_str(cur->token, NULL, -1);
		if (cur->type == DQUOTE)
			cur->token = check_dquote(cur->token);
	}
	return (1);
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
