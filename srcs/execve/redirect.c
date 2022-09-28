/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: siokim <siokim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/17 13:44:11 by siokim            #+#    #+#             */
/*   Updated: 2022/09/29 06:03:45 by siokim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	redirin(t_cmd *node)
{
	int fdin;
	
	fdin = openfile(node->next->next->cmd, INFILE);
	dup2(fdin, STDIN_FILENO);
	ft_cmd(node->cmd);
}

void	redirout(t_cmd *node)
{
	int	fdout;

	fdout = openfile(node->next->next->cmd, OUTFILE);
	dup2(fdout, STDOUT_FILENO);
	ft_cmd(node->cmd);
}


void	append(t_cmd *node)
{
	int	fdout;

	fdout = openfile(node->next->next->cmd, APPEND);
	dup2(fdout, STDOUT_FILENO);
	ft_cmd(node->cmd);

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

void	ft_redirect(t_cmd *node)
{
	if (node->type == REDIRIN)
		redirin(node);
	else if (node->type == REDIROUT)
		redirout(node);	
	else if (node->type == APPEND)
		append(node);
	// else
		// heredoc(node);
}