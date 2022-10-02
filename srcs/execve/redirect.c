/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: siokim <siokim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/17 13:44:11 by siokim            #+#    #+#             */
/*   Updated: 2022/10/03 03:56:53 by siokim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	redirin(t_cmd *node)
{
	int fdin;
	
	while (node != 0)
	{
		if (node->type == REDIRIN)
		{
			fdin = openfile(node->next->cmd, INFILE);
			dup2(fdin, STDIN_FILENO);
		}
		node = node->next;
	}
}


void	redirout(t_cmd *node)
{
	int	fdout;
	
	while (node != 0)
	{
		if (node->type == REDIROUT)
		{
			fdout = openfile(node->next->cmd, OUTFILE);
			dup2(fdout, STDOUT_FILENO);
			close(fdout);
		}
		node = node->next;
	}
}


void	append(t_cmd *node)
{
	int	fdout;

	while (node != 0)
	{
		if (node->type == REDIROUT)
		{
			fdout = openfile(node->next->cmd, APPEND);
			dup2(fdout, STDOUT_FILENO);
		}
		node = node->next;
	}
}

void	ft_redirect(t_cmd *node)
{
	redirin(node);
	redirout(node);
	append(node);
}

// void	heredoc(t_cmd *node)
// {
// 	char *end_str = node->right;
// 	while (1)
// 	{
// 		str = readline("> ");
// 		if (!ft_strncmp(str, end_str))
// 		{
// 			ft_cmd(envp, str);

// 		}
// 	}
//