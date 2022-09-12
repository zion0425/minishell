/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yjoo <yjoo@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 20:20:41 by yjoo              #+#    #+#             */
/*   Updated: 2022/09/12 20:29:14 by yjoo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	is_empty(char *line)
{
	int	idx;

	idx = -1;
	while (line[++idx])
	{
		if (line[idx] != ' ' && !(line[idx] >= 9 && line[idx] <= 13))
			return (0);
	}
	return (1);
}
