/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: siokim <siokim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 03:18:32 by siokim            #+#    #+#             */
/*   Updated: 2022/10/06 05:47:44 by siokim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	get_argc(t_cmd *cmd)
{
	int		ret;
	t_cmd	*cur;

	cur = cmd;
	ret = 0;
	while (cur)
	{
		ret++;
		cur = cur->next;
	}
	return (ret);
}

static int	ft_isalnums(char *str)
{
	int	size;
	int	i;

	i = -1;
	size = ft_strlen(str);
	while (++i < size && ft_strncmp(&str[i], "=", 1))
		if (!ft_isdigit(str[i]) && !ft_isalpha(str[i]))
			return (1);
	return (0);
}

static int	word_check(char c, char *str)
{
	if (ft_isdigit(c) || !ft_strncmp(&c, "=", 1) || !ft_strncmp(&c, "\0", 1))
	{
		printf("minishell: export: `%s`: not a vaild identifiers\n", str);
		return (-1);
	}
	if (ft_isalnums(str))
	{
		printf("minishell: export: `%s`: not a vaild identifier\n", str);
		return (-1);
	}
	return (1);
}

char	**new_envp(char *str, int size)
{
	int		i;
	char	**new;

	i = -1;
	new = (malloc(sizeof(char *) * (size + 2)));
	if (!new)
		return (0);
	new[size] = ft_strdup(str);
	new[size + 1] = ft_strdup(str);
	while (++i < size)
		new[i] = ft_strdup(g_var.envp[i]);
	new[i] = ft_strdup(str);
	new[i + 1] = 0;
	return (new);
}

void	export(t_cmd **node)
{
	int		idx;
	int		argc;

	idx = -1;
	argc = get_argc(*node);
	(*node) = (*node)->next;
	if (argc == 1)
		while (g_var.envp[++idx])
			if (ft_strncmp(g_var.envp[idx], "", 1))
				printf("%s\n", g_var.envp[idx]);
	if (argc == 2)
	{
		if (word_check((*node)->cmd[0], (*node)->cmd) == -1)
			return ((void)((*node) = (*node)->next));
		tmp_unset((*node)->cmd);
		idx = 0;
		while (g_var.envp[idx])
			idx++;
		g_var.envp = new_envp((*node)->cmd, idx);
	}
	while (--argc)
		(*node) = (*node)->next;
}
