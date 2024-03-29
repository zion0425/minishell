/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: siokim <siokim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 23:16:32 by yjoo              #+#    #+#             */
/*   Updated: 2022/10/06 09:47:12 by siokim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*find_value(char *key, char *ret, int idx, int jdx)
{
	char	**split;

	while (g_var.envp[++idx])
	{
		if (ft_strncmp(g_var.envp[idx], key, ft_strlen(key)) == 0)
		{
			split = ft_split(g_var.envp[idx], '=');
			if (ft_strcmp(split[0], key) == 0)
			{
				jdx = ft_strlen(key) + 1;
				while (g_var.envp[idx][jdx])
					jdx++;
				ret = ft_substr(g_var.envp[idx], ft_strlen(key) + 1, \
				jdx - (ft_strlen(key) + 1));
				free(key);
				free_split(split);
				return (ret);
			}
			else
				free_split(split);
		}
	}
	ret = ft_strdup("");
	free(key);
	return (ret);
}

char	*dollar_question(char *str)
{
	int		idx;
	char	*exit_code;
	char	*tmp;
	char	*ret;

	idx = 1;
	exit_code = ft_itoa(g_var.exit_code);
	while (str[idx])
		idx++;
	tmp = ft_substr(str, 1, idx);
	ret = ft_strjoin(exit_code, tmp);
	free(tmp);
	free(exit_code);
	return (ret);
}

char	*reassembly_str(char *cur, char *tmp, int idx)
{
	char	*ret;
	char	*value;

	if (cur[0] == '?')
		ret = dollar_question(cur);
	else
	{
		while (cur[++idx])
		{
			if (!ft_isalnum(cur[idx]) || (ft_isdigit(cur[0]) && idx == 1))
			{
				tmp = ft_substr(cur, idx, ft_strlen(cur) - idx);
				break ;
			}
		}
		if (!tmp && cur[idx] == '\0')
			tmp = ft_strdup("");
		value = find_value(ft_substr(cur, 0, idx), NULL, -1, 0);
		ret = ft_strjoin(value, tmp);
		free(tmp);
		free(value);
	}
	free(cur);
	return (ret);
}

char	*dquote_dollar(char *cur, char *ret, char *join, int idx)
{
	int		start;
	char	*tmp;

	while (cur[idx])
	{
		if (cur[idx] == '$')
		{
			start = idx + 1;
			while (cur[++idx] && ft_isalnum(cur[idx]))
				;
			join = reassembly_str(ft_substr(cur, start, idx - start), NULL, -1);
		}
		else
		{
			start = idx;
			while (cur[idx] && cur[idx] != '$')
				idx++;
			join = ft_substr(cur, start, idx - start);
		}
		tmp = ret;
		ret = ft_strjoin(ret, join);
		free(tmp);
		free(join);
	}
	return (ret);
}

int	envp_convert(t_token *head, int cnt)
{
	int		idx;
	char	*tmp;
	t_token	*cur;

	idx = -1;
	cur = head;
	while (++idx < cnt)
	{
		if (cur->type == DOLLAR)
			cur->token = reassembly_str(cur->token, NULL, -1);
		if (cur->type == DQUOTE)
		{
			tmp = cur->token;
			cur->token = dquote_dollar(cur->token, ft_strdup(""), NULL, 0);
			free(tmp);
		}
		if (cur->token == NULL)
			return (0);
		cur = cur->next;
	}
	return (1);
}
