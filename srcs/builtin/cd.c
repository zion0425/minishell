/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: siokim <siokim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 06:31:03 by yjoo              #+#    #+#             */
/*   Updated: 2022/10/06 06:10:18 by siokim           ###   ########.fr       */
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

static void	_cd(t_cmd *cmd)
{
	char	*tmp;

	if (cmd->cmd && cmd->cmd[0] != '~')
	{
		if (chdir(cmd->cmd) == -1)
		{
			printf("minishell: cd: %s: %s\n", "??path??", strerror(errno));
			g_var.exit_code = 1;
		}
	}
	else if (ft_strcmp(cmd->cmd, "") == 0 || cmd->cmd[0] == '~')
	{
		if (cmd->cmd[1])
			printf("minishell: cd: %s: No such file or directory\n", cmd->cmd);
		else
		{
			tmp = find_value(ft_strdup("HOME"), NULL, -1, 0);
			if (chdir(tmp) == -1)
				printf("minishell: cd: Unable to find home\n");
			free(tmp);
		}
		g_var.exit_code = 1;
	}
}

void	cd(t_cmd *cmd, int size)
{
	if (size > 0)
		return ;
	if (get_argc(cmd) > 2)
	{
		printf("minishell: cd: too many arguments\n");
		g_var.exit_code = 1;
		return ;
	}
	_cd(cmd->next);
}
