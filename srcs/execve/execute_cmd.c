/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: siokim <siokim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 06:46:33 by siokim            #+#    #+#             */
/*   Updated: 2022/10/03 08:45:27 by siokim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*getpath(char *cmd)
{
	int			i;
	char		*path;
	char		**paths;
	char		*res_path;
	struct stat	buf;

	i = -1;
	while (g_var.envp[++i] != NULL)
		if (!ft_strncmp(g_var.envp[i], "PATH=", 5))
			break ;
	if (ft_strchr(cmd, '/') || g_var.envp[i] == NULL)
		return (cmd);
	path = &g_var.envp[i][5];
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

char	*get_cmds(t_cmd **node)
{
	char	*tmp_cmd;

	tmp_cmd = (*node)->cmd;
	while ((*node)->next != 0 && (*node)->next->type == WORD)
	{
		tmp_cmd = ft_strjoin(tmp_cmd, ft_strjoin(" ", (*node)->next->cmd));
		(*node) = (*node)->next;
	}
	return (tmp_cmd);
}

void	ft_cmd(char *cmd)
{
	char	*path;
	char	**cmds;
	int		pid;

	pid = fork();
	if (pid == 0)
	{
		cmds = ft_split(cmd, ' ');
		path = getpath(cmds[0]);
		execve(path, cmds, g_var.envp);
		write(2, cmd, ft_strlen(cmd));
		write(2, ": command not found\n", 20);
		exit(127);
	}
	waitpid(pid, 0, 0);
}

void	ft_simplecmd(char *cmd)
{
	char	*path;
	char	**cmds;

	cmds = ft_split(cmd, ' ');
	path = getpath(cmds[0]);
	execve(path, cmds, g_var.envp);
	write(2, cmd, ft_strlen(cmd));
	write(2, ": command not found\n", 20);
	exit(127);
}