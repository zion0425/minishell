/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yjoo <yjoo@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 04:49:31 by yjoo              #+#    #+#             */
/*   Updated: 2022/10/03 06:13:49 by yjoo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	exit_msg(char *str, int code)
{
	ft_putstr_fd("exit\n", 1);
	ft_putstr_fd(str, 1);
	g_var.exit_code = code;
	exit(g_var.exit_code);
}

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

void	ft_exit(t_cmd *cmd, int size)
{
	int		argc;
	int		idx;
	t_cmd	*cur;

	argc = get_argc(cmd);
	if (size > 1)
		return ;
	if (argc == 1)
		exit_msg("", g_var.exit_code);
	else if (argc >= 2)
	{
		cur = cmd->next;
		idx = 0;
		while (ft_isdigit(cmd->cmd[idx]))
			idx++;
		if (cur->cmd[idx] == '\0' && argc == 2)
			exit_msg("", ft_atoi(cur->cmd));
		else if (cur->cmd[idx] != '\0' && argc >= 2)
			exit_msg("minishell: exit: numeric argument required\n", 1);
		else if (cur->cmd[idx] == '\0' && argc > 2)
			exit_msg("minishell: exit: too many arguments\n", 255);
	}
}
