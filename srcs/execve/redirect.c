/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: siokim <siokim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/17 13:44:11 by siokim            #+#    #+#             */
/*   Updated: 2022/09/22 15:44:37 by siokim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_redirect(char **envp, t_node *node)
{
	if (node->type == REDIRIN)
		redirin(node);
    else if (node->type == REDIROUT)
		redirout(node);	
    else if (node->type == APPEND)
		append(node);
	else 
		heredoc(node);
}

void    redirin(t_node *node)
{
	int	fdin;

	fdin = fileopen(node->/*right | left ->file_path | dir_path*/, INFILE);
	dup2(fdin, STDIN_FILENO);
}

void    redirout(t_node *node)
{
	int	fdout;

	fdout = fileopen(node->right/*->file_path*/, OUTFILE);
	dup2(fdout, STDOUT_FILENO);
	ft_execve(node->left);
}


void    apeend(t_node *node)
{
	int	fdout;

	fdout = fileopen(node->right/*->file_path*/, APPEND);
	dup2(fdout, STDOUT_FILENO);
	ft_cmd(node->left);
}

void    heredoc(t_node *node)
{
    char *end_str = node->right;
    while (1)
    {
        str = readline("> ");
        if (!ft_strncmp(str, end_str))
        {
            ft_cmd(envp, str);
            
        }
    }
}

