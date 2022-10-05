/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: siokim <siokim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 03:18:32 by siokim            #+#    #+#             */
/*   Updated: 2022/10/06 04:10:26 by siokim           ###   ########.fr       */
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
	size_t	size;

	size = ft_strlen(str);
	while (size--)
		if (!ft_isdigit(str[size]) && !ft_isalpha(str[size]))
			return (1);
	return (0);
}

static int	word_check(char c, char *str)
{
	if (ft_isdigit(c))
	{
		printf("minishell: export: `%s`: not a vaild identifier", str);
		return (-1);
	}
	if (ft_isalnums(str))
	{
		printf("minishell: export: `%s`: not a vaild identifier", str);
		return (-1);
	}
	return (1);
}

void	export(t_cmd **node)
{
	int	idx;
	int	argc;

	idx = -1;
	argc = get_argc(*node);
	if (argc == 1)
	{
		while (g_var.envp[++idx])
			if (ft_strncmp(g_var.envp[idx], "", 1))
				printf("%s\n", g_var.envp[idx]);
	}
	else if (argc == 2)
	{
		if (word_check((*node)->cmd[0],(*node)->cmd) == -1)
			return ;
		idx = 0;
		while (g_var.envp[idx])
			idx++;
		g_var.envp[idx-1] = (*node)->cmd;
		while (--argc)
			(*node)=(*node)->next;
	}
	else
		return ;
	(*node)=(*node)->next;
}
