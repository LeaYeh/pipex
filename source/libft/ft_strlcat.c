/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lyeh <lyeh@student.42vienna.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 15:37:01 by lyeh              #+#    #+#             */
/*   Updated: 2023/09/11 16:29:44 by lyeh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	const size_t	src_len = ft_strlen(src);
	const size_t	dst_len = ft_strlen(dst);

	if (!dst || !src || dstsize == 0)
		return (src_len);
	if (dstsize > dst_len)
	{
		ft_strlcpy(dst + dst_len, src, dstsize - dst_len);
		return (src_len + dst_len);
	}
	return (src_len + dstsize);
}
