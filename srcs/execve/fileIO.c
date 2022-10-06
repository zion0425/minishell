/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fileIO.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: siokim <siokim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 11:22:51 by siokim            #+#    #+#             */
/*   Updated: 2022/10/06 13:32:47 by siokim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	print_error(char *err_msg)
{
	printf("%s : %s\n", err_msg, strerror(errno));
	return (-1);
}

int	openfile(char *filename, char format)
{
	int			fdin;
	int			fdout;
	struct stat	buf;

	if (format == INFILE)
	{
		if (stat(filename, &buf) == -1)
			return (print_error(filename));
		fdin = open(filename, O_RDONLY);
		if (fdin == -1)
			return (print_error(filename));
		return (fdin);
	}
	else
	{
		if (format == APPEND)
			fdout = open(filename, O_CREAT | O_WRONLY | O_APPEND, 0755);
		else
			fdout = open(filename, O_CREAT | O_WRONLY | O_TRUNC, 0755);
		if (fdout == -1)
			return (print_error(filename));
		return (fdout);
	}
}	
