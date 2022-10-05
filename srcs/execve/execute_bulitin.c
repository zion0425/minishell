/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_bulitin.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: siokim <siokim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 22:22:44 by siokim            #+#    #+#             */
/*   Updated: 2022/10/06 03:48:30 by siokim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_bulitin(t_cmd **node, int size)
{
	// if (ft_strncmp((*node)->cmd, "cd", 4))
	// 	cd(*node, size);
	if (!ft_strncmp((*node)->cmd, "echo", 4))
		echo(node);
	else if (!ft_strncmp((*node)->cmd, "env", 4))
	{
		env();
		(*node)=(*node)->next;
	}
	else if (!ft_strncmp((*node)->cmd, "pwd", 4))
	{
		pwd();
		(*node)=(*node)->next;
	}
	else if (!ft_strncmp((*node)->cmd, "unset", 5))
	{
		unset(*node);
		(*node)=(*node)->next->next;
	}
	else if (!ft_strncmp((*node)->cmd, "exit", 4))
		ft_exit(node, size);
	else if (!ft_strncmp((*node)->cmd, "export", 6))
	{
		export(node);
	}
}