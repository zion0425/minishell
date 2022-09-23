/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yjoo <yjoo@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 20:20:41 by yjoo              #+#    #+#             */
/*   Updated: 2022/09/23 08:01:12 by yjoo             ###   ########.fr       */
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

char	**get_envp(char **envp)
{
	int		idx;
	char	**ret;

	idx = 0;
	while (envp[idx])
		idx++;
	ret = ft_calloc(sizeof(char *), idx + 1);
	if (!ret)
		return (NULL);
	idx = -1;
	while (envp[++idx])
		ret[idx] = ft_strdup(envp[idx]);
	ret[idx] = NULL;
	return (ret);
}
