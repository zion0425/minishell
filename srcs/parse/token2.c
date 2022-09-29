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

char	*dollar_qustion(char *str)
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
		ret = dollar_qustion(cur);
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

char	*dquote_dollar(char *cur)
{
	int		idx;
	char	*ret;
	char	*tmp;
	char	**split;

	idx = -1;
	if (ft_strlen(cur) == 0)
		return (cur);
	ret = ft_strdup("");
	split = ft_split(cur, '$');
	while (split[++idx])
	{
		tmp = ret;
		ret = ft_strjoin(ret, reassembly_str(split[idx], NULL, -1));
		free(tmp);
	}
	free_split(split);
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
			cur->token = dquote_dollar(cur->token);
		cur = cur->next;
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
