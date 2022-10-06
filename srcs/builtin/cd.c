/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: siokim <siokim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 06:31:03 by yjoo              #+#    #+#             */
/*   Updated: 2022/10/06 09:34:46 by siokim           ###   ########.fr       */
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

static void	set_oldpath(char *old_path)
{
	int		idx;

	idx = 0;
	tmp_unset(old_path);
	while (g_var.envp[idx])
		idx++;
	g_var.envp = new_envp(old_path, idx);
}

static void	_cd(t_cmd *cmd)
{
	char	*tmp;

	if (cmd->cmd && cmd->cmd[0] != '~')
	{
		if (chdir(cmd->cmd) == -1)
		{
			printf("minishell: cd: %s: %s\n", cmd->cmd, strerror(errno));
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

void	cd(t_cmd **node, int size)
{
	int		argc;
	char	*old_path;

	old_path = get_pwd();
	old_path = ft_strjoin("OLDPWD=", old_path);
	argc = get_argc(*node);
	if (size > 0)
		return ;
	else if (argc <= 1)
		return ;
	else if (argc > 2)
	{
		printf("minishell: cd: too many arguments\n");
		g_var.exit_code = 1;
		while (--argc > 0)
			(*node) = (*node)->next;
		return ;
	}
	_cd((*node)->next);
	if (g_var.exit_code == 0)
		set_oldpath(old_path);
	while (--argc > 0)
		(*node) = (*node)->next;
}
