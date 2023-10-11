/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lyeh <lyeh@student.42vienna.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 20:44:49 by lyeh              #+#    #+#             */
/*   Updated: 2023/09/09 11:05:22 by lyeh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *dst, int val, size_t len)
{
	unsigned char	*ptr;

	ptr = (unsigned char *) dst;
	while (len-- > 0)
		*ptr++ = (unsigned char)val;
	return (dst);
}
