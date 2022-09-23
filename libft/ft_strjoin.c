/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yjoo <yjoo@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 18:42:35 by yjoo              #+#    #+#             */
/*   Updated: 2021/12/16 16:32:28 by yjoo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char *s1, char *s2)
{
	size_t	str_size;
	char	*str;

	if (!s1)
	{
		s1 = (char *)malloc(sizeof(char) * 1);
		s1[0] = 0;
	}
	if (!s1 || !s2)
		return (NULL);
	str_size = ft_strlen(s1) + ft_strlen(s2);
	str = (char *)malloc(sizeof(char) * (str_size + 1));
	if (!str)
		return (NULL);
	ft_strlcpy(str + ft_strlcpy(str, s1, (str_size + 1)), s2, (str_size + 1));
	free(s1);
	return (str);
}
