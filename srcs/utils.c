/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yjoo <yjoo@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 13:10:39 by yjoo              #+#    #+#             */
/*   Updated: 2022/09/23 13:10:39 by yjoo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

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
