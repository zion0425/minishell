/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: siokim <siokim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 09:19:20 by siokim            #+#    #+#             */
/*   Updated: 2022/10/06 12:28:25 by siokim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	heredoc(t_cmd *node)
{
	int		fd;
	char	*str;

	fd = open(".tmp", O_WRONLY | O_CREAT | O_TRUNC, 0777);
	while (node != 0)
	{
		if (node->type == HEREDOC)
		{
			signal_setting(1);
			while (1)
			{
				str = readline("> ");
				if (str == NULL)
					return (-1);
				if (!ft_strncmp(str, node->next->cmd, ft_strlen(str)))
					break ;
				write (fd, str, ft_strlen(str));
				write (fd, "\n", 1);
			}
		}
		node = node->next;
	}
	fd = open(".tmp", O_RDONLY, 0777);
	dup2(fd, STDIN_FILENO);
	return (0);
}
