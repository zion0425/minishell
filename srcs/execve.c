/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: siokim <siokim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/10 18:14:23 by siokim            #+#    #+#             */
/*   Updated: 2022/09/17 13:46:05 by siokim           ###   ########.fr       */
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

void	ft_cmd(char **envp, t_node node)
{
	char	*path;
	char	**cmds;
	int		pid;

	pid = fork();
	if (pid == 0)
	{
		cmds = ft_split(cmd, ' ');
		path = getpath(envp, cmds[0]);
		execve(path, cmds, envp);
		write(2, cmd, ft_strlen(cmd));
		write(2, ": command not found\n", 20);
		exit(127);
	}
	waitpid(pid , 0, 0);
}

void	ft_execve(char **envp, t_node *node)
{
	if (node != NULL)
	{
	
		if (node->type == PIPE)
		{
			ft_pipe();

			//start ft_pipe function
			int pid;

			pid = fork();
			if (pid == 0)
				ft_execve(node->right);
			else if (pid > 0)
				// ft_execve(node->left);
				// 부모 프로세스 이므로 그냥 처리 안 함
			else
				write(2, "fork_error\n", 11);
			//end ft_pipe
			ft_execve(node->left);
		}
		
		if (node->type == REDIRECT)
		{
			ft_redirect()

			// start ft_redirect function
			// https://www.gnu.org/software/bash/manual/html_node/Redirections.html
			
			if (node->type == REDIRIN)
			// 유효성 검사 '<'
			// if (node->right word)
			
			else if (node->type == REDIROUT)
			// 유효성 검사?? '>'
			// left가 없을 경우 touch file
			// if (node->right)
			
			else if (node->type == APPEND)
			// 유효성 검사 '>>'
			// left가 없을 경우 touch file
			// if node->left cmd | node -> left file

			else if (node->type == HEREDOC)
			// 유효성 검사 '<<'
			// if node->left cmd | node -> left file
			/* 여기까지.
			char *end_str = node->right;
			while (1)
			{
				
				str = readline("> ");
				if (!ft_strncmp(str, end_str))
				{
					ft_cmd(envp, str);
					
				}
			}
			*/
			// end ft_redirect function	
		}

		ft_execve(envp, node->left);
	}

	else if (node->right != NULL)
		ft_execve(node->right);

	else
		ft_cmd(envp, node);

}

void	ft_pipe(char **envp, char *cmd)
{
	int	pid;
	
	// 유효성 검사
	// pipe 앞에 cmd가 없을 경우 error
	// pipe 뒤에 cmd가 없을 경우 readline (pipe> ) 실행하여 cmd 값 추가 입력
	pid = fork();
	if (pid == 0)
		ft_execve(envp, /*cmd,*/ lst);
	else if(pid > 0)
		write(2, "fork error\n", 11);

}

void	ft_redirect()
{
	// redirect 앞 뒤에 올바른 값이 들어갔는지 예외 처리
	// dup 로 stdin stdout 설정.
	// 
}

void	ft_echo()
{
	
}

void	ft_cd()
{
	
}

// bulit in 함수로 cd 구현시 pwd 경로를 잡아주는지 확인 필요.
void	ft_pwd();
void	ft_export();
void	ft_unset();
void	ft_env();
void	ft_exit();