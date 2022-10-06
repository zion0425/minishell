/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: siokim <siokim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/17 13:44:11 by siokim            #+#    #+#             */
/*   Updated: 2022/10/06 13:14:13 by siokim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	redirin(t_cmd *node)
{
	int	fdin;

	while (node != 0)
	{
		if (node->type == REDIRIN)
		{
			fdin = openfile(node->next->cmd, INFILE);
			if (fdin == -1)
				return (-1);
			dup2(fdin, STDIN_FILENO);
		}
		node = node->next;
	}
	return (0);
}

int	redirout(t_cmd *node)
{
	int	fdout;

	while (node != 0)
	{
		if (node->type == REDIROUT)
		{
			fdout = openfile(node->next->cmd, OUTFILE);
			if (fdout == -1)
				return (-1);
			dup2(fdout, STDOUT_FILENO);
		}
		node = node->next;
	}
	return (0);
}

int	append(t_cmd *node)
{
	int	fdout;

	while (node != 0)
	{
		if (node->type == REDIROUT)
		{
			fdout = openfile(node->next->cmd, APPEND);
			if (fdout == -1)
				return (-1);
			dup2(fdout, STDOUT_FILENO);
		}
		node = node->next;
	}
	return (0);
}

int	ft_redirect(t_cmd *node, int size)
{
	int	iserr;

	iserr = 0;
	iserr += redirin(node);
	if (size <= 0)
		iserr += heredoc(node);
	iserr += redirout(node);
	iserr += append(node);
	if (iserr > 0)
		iserr = -1;
	return (iserr);
}
