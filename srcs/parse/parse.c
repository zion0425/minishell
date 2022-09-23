/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yjoo <yjoo@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/11 13:41:15 by yjoo              #+#    #+#             */
/*   Updated: 2022/09/23 08:08:10 by yjoo             ###   ########.fr       */
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

int	create_parse_tree(t_cmd_list cmd_list, t_token *head_token)
{
	envp_to_word(head_token);
	//syntax_pipe(head_token);
}

int	create_token_list(char *line, t_token **head_token)
{
	int	idx;

	idx = 0;
	while (line[idx])
	{
		while (line[idx] && (line[idx] == ' ' || \
		(line[idx] >= 9 && line[idx] <= 13)))
			idx++;
		if (!line[idx])
			return (0);
		if (!new_token(head_token, line, &idx))
			return (0);
		idx++;
	}
	return (1);
}

int	parse(t_cmd_list *cmd_list)
{
	char	*line;
	t_token	*head_token;

	prompt(&line);
	if (is_empty(line))
	{
		if (line)
			free(line);
		return (0);
	}
	head_token = NULL;
	if (!create_token_list(line, &head_token))
	{
		free_token_list(head_token);
		if (line)
			free(line);
		return (0);
	}
	add_history(line);
	free(line);
	free_token_list(head_token);
	return (1);
}
