/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yjoo <yjoo@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 06:20:42 by yjoo              #+#    #+#             */
/*   Updated: 2022/10/03 06:58:57 by yjoo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	pwd(void)
{
	char	*cur_dir;

	cur_dir = getcwd(NULL, 1024);
	if (!cur_dir)
		printf("getpwd() error\n");
	else
	{
		printf("%s\n", cur_dir);
		free(cur_dir);
	}
}
