/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yjoo <yjoo@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/11 13:41:15 by yjoo              #+#    #+#             */
/*   Updated: 2022/09/12 20:50:45 by yjoo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	prompt(char **line)
{
	*line = readline("minishell$> ");
	if (*line == NULL)
	{	
		ft_putstr_fd("\x1b[1A\033[12Cexit\n", STDOUT_FILENO);
		exit(EXIT_SUCCESS);
	}
}

int	create_token_list(char *line, t_token **token_head)
{
	int	idx;

	idx = 0;
	while (line[idx] && line[idx] == ' ' || (line[idx] >= 9 && line[idx] <= 13))
		idx++;
	while (line[idx])
	{
		
	}
	return (1);
}

int	parse(void)
{
	char	*line;
	t_token	*token_head;

	prompt(&line);
	if (is_empty(line))
	{
		free(line);
		return (0);
	}
	create_token_list(line, &token_head);
	add_history(line);
	free(line);
}
