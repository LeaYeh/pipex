/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lyeh <lyeh@student.42vienna.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 15:29:08 by lyeh              #+#    #+#             */
/*   Updated: 2023/09/11 16:31:08 by lyeh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
1. if src_len (inculed null char) is smaller than dstsize, 
	copy entire src array with null char
2. otherwise, copy up to dstsize-1 characters and NUL-terminating 
	the result if dstsize is not 0 
*/
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	const size_t	src_len = ft_strlen(src);

	if (src_len + 1 < dstsize)
		ft_memcpy(dst, src, src_len + 1);
	else if (dstsize != 0)
	{
		ft_memcpy(dst, src, dstsize - 1);
		dst[dstsize - 1] = '\0';
	}
	return (src_len);
}
