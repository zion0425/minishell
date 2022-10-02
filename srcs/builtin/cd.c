/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yjoo <yjoo@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 06:31:03 by yjoo              #+#    #+#             */
/*   Updated: 2022/10/03 06:58:26 by yjoo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	cd(t_cmd *cmd)
{
	char	*tmp;

	cmd = cmd->next;
	if (cmd->cmd && cmd->cmd[0] != '~')
	{
		if (chdir(cmd->cmd) == -1)
		{
			printf("minishell: cd: %s: %s\n", path, strerror(errno));
			g_var.exit_code = 1;
		}
	}
	else if (ft_strcmp(cmd->cmd, "") == 0 || cmd->cmd[0] == '~')
	{
		if (cmd->cmd[1])
		{
			printf("minishell: cd: %s: No such file or directory\n", cmd->cmd);
			g_var.exit_code = 1;
		}
		else
		{
			tmp = find_value(ft_strdup("HOME"), NULL, -1, 0);
			if (chdir(tmp) == -1)
				printf("minishell: cd: Unable to find home\n");
			g_var.exit_code = 1;
			free(tmp);
		}
	}
}
