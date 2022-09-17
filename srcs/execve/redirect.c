/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: siokim <siokim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/17 13:44:11 by siokim            #+#    #+#             */
/*   Updated: 2022/09/17 13:44:14 by siokim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void    ft_redirect(t_node *node)
{
    if (node->type == REDIRIN)
    {
        if (node -> right -> type)
        redirin(node);
    }
    else if (node->type == REDIROUT)
    {

    }
    else if (node->type == APPEND)
    {

    }
    else if (node->type == HEREDOC)
    {

    }
}

void    redirin(t_node *node)
{
    // 유효성 검사 '<'
    // if (node->right word)
}

void    redirout(t_node *node)
{
    // 유효성 검사?? '>'
    // left가 없을 경우 touch file
    // if (node->right)
}

void    apeend(t_node *node)
{
    // 유효성 검사 '>>'
    // left가 없을 경우 touch file
    // if node->left cmd | node -> left file
}

void    heredoc(t_node *node)
{
    // 유효성 검사 '<<'
    // if node->left cmd | node -> left file
    /* 여기까지.
    char *end_str = node->right;
    while (1)
    {
        
        str = readline("> ");
        if (!ft_strncmp(str, end_str))
        {
            ft_cmd(envp, str);
            
        }
    }
    */
    // end ft_redirect function 
}
