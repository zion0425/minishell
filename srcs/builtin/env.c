/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: siokim <siokim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/01 21:31:36 by yjoo              #+#    #+#             */
/*   Updated: 2022/10/06 03:28:51 by siokim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	env(void)
{
	int	idx;

	idx = -1;
	while (g_var.envp[++idx])
		if (ft_strncmp(g_var.envp[idx], "", 1))
			printf("%s\n", g_var.envp[idx]);
	g_var.exit_code = 0;
}
