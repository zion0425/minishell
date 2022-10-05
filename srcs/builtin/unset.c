/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: siokim <siokim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/01 21:47:55 by yjoo              #+#    #+#             */
/*   Updated: 2022/10/05 22:56:18 by siokim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	unset(t_cmd *cmd)
{
	int	idx;

	idx = -1;
	while (g_var.envp[++idx])
		if (!ft_strncmp(g_var.envp[idx], cmd->next->cmd, ft_strlen(cmd->next->cmd)))
			g_var.envp[idx] = "";
	g_var.exit_code = 0;
}
