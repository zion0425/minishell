/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: siokim <siokim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/10 18:14:23 by siokim            #+#    #+#             */
/*   Updated: 2022/09/11 14:03:36 by siokim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*getpath(char **envp, char *cmd)
{
	int			i;
	char		*path;
	char		**paths;
	char		*res_path;
	struct stat	buf;

	i = -1;
	while (envp[++i] != NULL)
		if (!ft_strncmp(envp[i], "PATH=", 5))
			break ;
	if (ft_strchr(cmd, '/') || envp[i] == NULL)
		return (cmd);
	path = &envp[i][5];
	paths = ft_split(path, ':');
	i = -1;
	while (paths[++i])
	{
		res_path = ft_strjoin(ft_strjoin(paths[i], "/"), cmd);
		if (stat(res_path, &buf) != -1)
			return (res_path);
		free(res_path);
	}
	write(2, cmd, ft_strlen(cmd));
	write(2, ": command not found\n", 20);
	exit(127);
}

void	ft_execve(char **envp, char *cmd)
{
	char	*path;
	char	**cmds;

	cmds = ft_split(cmd, ' ');
	path = getpath(envp, cmds[0]);
	execve(path, cmds, envp);
	write(2, cmd, ft_strlen(cmd));
	write(2, ": command not found\n", 20);
	exit(127);
}
