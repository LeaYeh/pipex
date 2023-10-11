/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lyeh <lyeh@student.42vienna.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 13:31:59 by lyeh              #+#    #+#             */
/*   Updated: 2023/09/10 15:28:22 by lyeh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
If the buffers don't overlap, it doesn't matter what direction
we copy in. If they do, it does, so just assume they always do.
We don't concern ourselves with the possibility that the region
to copy might roll over across the top of memory, because it's
not going to happen.
If the destination is above the source, we have to copy
back to front to avoid overwriting the data we want to
copy.
     dest:       dddddddd
     src:    ssssssss   ^
             |   ^  |___|
             |___|
If the destination is below the source, we have to copy
front to back.
      dest:   dddddddd
      src:    ^   ssssssss
              |___|  ^   |
                     |___|
*/
void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char		*dst_ptr;
	const unsigned char	*src_ptr;

	dst_ptr = dst;
	src_ptr = src;
	if (!dst_ptr && !src_ptr)
		return (NULL);
	if (dst_ptr <= src_ptr || (dst_ptr >= (src_ptr + len)))
		ft_memcpy(dst_ptr, src_ptr, len);
	else
	{
		while (len && len-- > 0)
			dst_ptr[len] = src_ptr[len];
	}
	return (dst);
}
