/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yjoo <yjoo@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 04:49:31 by yjoo              #+#    #+#             */
/*   Updated: 2022/10/03 05:06:40 by yjoo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_exit(t_cmd *cmd, int size)
{
	int		argc;
	t_cmd	*cur;

	argc = 0;
	if (size > 1)
		return ;
	while (cur)
	{
		argc++;
		cur = cur->next;
	}
	if (argc == 1)
	{
		ft_putstr_fd("exit\n", 1);
		exit (0);
	}
}
