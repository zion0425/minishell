/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yjoo <yjoo@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/02 21:42:02 by yjoo              #+#    #+#             */
/*   Updated: 2022/10/03 04:17:25 by yjoo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	check_option(t_cmd *cur)
{
	int	idx;

	if (ft_strncmp(cur->cmd, "-n", 2) == 0)
	{
		idx = 2;
		while (cur->cmd[idx] && cur->cmd[idx] == 'n')
			idx++;
		if (cur->cmd[idx] == '\0')
			return (1);
		else
			return (0);
	}
	return (0);
}

void	echo(t_cmd *head_cmd)
{
	int		flag;
	t_cmd	*cur;

	cur = head_cmd->next;
	flag = check_option(cur);
	if (flag)
		cur = cur->next;
	while (cur)
	{
		ft_putstr_fd(cur->cmd, 1);
		if (cur->next)
			ft_putchar_fd(' ', 1);
		cur = cur->next;
	}
	if (!flag)
		ft_putchar_fd('\n', 1);
	g_var.exit_code = 0;
}
