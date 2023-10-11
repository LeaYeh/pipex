/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lyeh <lyeh@student.42vienna.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/09 11:02:11 by lyeh              #+#    #+#             */
/*   Updated: 2023/09/10 13:33:46 by lyeh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char	*dst;
	size_t	src_len;

	src_len = ft_strlen(s1);
	dst = (char *)malloc(sizeof(char) * src_len + 1);
	if (dst == NULL)
		return (NULL);
	ft_memcpy(dst, s1, src_len + 1);
	return (dst);
}
