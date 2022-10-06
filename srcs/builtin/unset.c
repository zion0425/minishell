/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: siokim <siokim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/01 21:47:55 by yjoo              #+#    #+#             */
/*   Updated: 2022/10/06 09:10:57 by siokim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	unset(t_cmd *cmd)
{
	int	idx;

	idx = -1;
	while (g_var.envp[++idx])
		if (!ft_strncmp(g_var.envp[idx], \
		cmd->next->cmd, ft_strlen(cmd->next->cmd)))
			g_var.envp[idx] = "";
	g_var.exit_code = 0;
}

void	tmp_unset(char *str)
{
	int		idx;
	char	*tmp_str;

	idx = 0;
	tmp_str = 0;
	while (str[idx] && ft_strncmp(&str[idx], "=", 1))
		idx++;
	tmp_str = malloc(sizeof(char *) * (idx + 1));
	tmp_str[idx] = 0;
	while (idx--)
		tmp_str[idx] = str[idx];
	while (g_var.envp[++idx])
		if (!ft_strncmp(g_var.envp[idx], tmp_str, ft_strlen(tmp_str)))
			g_var.envp[idx] = "";
	free(tmp_str);
	tmp_str = 0;
}
