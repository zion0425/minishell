/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yjoo <yjoo@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 23:16:32 by yjoo              #+#    #+#             */
/*   Updated: 2022/09/23 09:22:02 by yjoo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	envp_to_word(t_token *head_token)
{
	int		idx;
	t_token	*cur_token;
	char	*tmp;
	char	**split;

	cur_token = serach_token(head_token, DOLLAR);
	split = ft_split(cur_token->token, '=');
	idx = -1;
	if (cur_token->type == DOLLAR)
	{
		while (g_envp[++idx])
		{
			if (ft_strncmp(split[0], g_envp[idx], ft_strlen(split[0]) == 0))
			{
				if (split[1] != NULL)
				{
					idx = -1;
					while (split[++idx])
						tmp = ft_strjoin(tmp, split[idx]);
				}
				else
					tmp = ft_strdup("");
				free_split(split);
				split = ft_split(g_envp[idx], '=');
				tmp = ft_strjoin(split[1], tmp);
			}
		}
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

void	free_split(char **split)
{
	size_t	i;

	i = 0;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
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
