/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yjoo <yjoo@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 20:20:41 by yjoo              #+#    #+#             */
/*   Updated: 2022/09/22 23:32:25 by yjoo             ###   ########.fr       */
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
