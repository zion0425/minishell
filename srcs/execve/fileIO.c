/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fileIO.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: siokim <siokim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 11:22:51 by siokim            #+#    #+#             */
/*   Updated: 2022/09/22 12:42:00 by siokim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	print_error(char *err_msg)
{
	printf("%s : %s\n", err_msg, strerror(errno));
	exit(1);
}

int	openfile(char *filename, char format)
{
	int			fdin;
	int			fdout;
	struct stat	buf;

	if (format == INFILE)
	{
		if (stat(filename, &buf) == -1)
			print_error(filename);
		fdin = open(filename, O_RDONLY);
		if (fdin == -1)
			print_error(filename);
		return (fdin);
	}
	else
	{
		fdout = open(filename, O_CREAT | O_WRONLY | O_TRUNC, 0755);
		if (fdout == -1)
			print_error(filename);
		return (fdout);
	}
}	
