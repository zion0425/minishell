/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: siokim <siokim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/17 13:44:11 by siokim            #+#    #+#             */
/*   Updated: 2022/09/22 19:14:48 by siokim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	redirin(t_cmd *node)
{
	int fdin;
	
	fdin = openfile(node->right->cmd, INFILE);
	dup2(fdin, STDIN_FILENO);
}

void	redirout(t_cmd *node, char **envp)
{
	int	fdout;

	fdout = openfile(node->right->cmd, OUTFILE);
	dup2(fdout, STDOUT_FILENO);
	ft_execve(envp, node->left);
}


void	append(t_cmd *node, char **envp)
{
	int	fdout;

	fdout = openfile(node->right->cmd, APPEND);
	dup2(fdout, STDOUT_FILENO);
	ft_cmd(envp, node->left->cmd);
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
// }

void	ft_redirect(char **envp, t_cmd *node)
{
	if (node->type == REDIRIN)
		redirin(node);
	else if (node->type == REDIROUT)
		redirout(node, envp);	
	else if (node->type == APPEND)
		append(node, envp);
	// else
		// heredoc(node);
}