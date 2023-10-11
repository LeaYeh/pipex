/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lyeh <lyeh@student.42vienna.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 20:41:38 by lyeh              #+#    #+#             */
/*   Updated: 2023/09/10 15:04:43 by lyeh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	_get_num_len(long num)
{
	size_t	len;

	len = 0;
	if (num == 0)
		len = 1;
	else if (num < 0)
	{
		num *= -1;
		len++;
	}
	while (num > 0)
	{
		num /= 10;
		len++;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	char	*ptr;
	long	long_n;
	size_t	len;

	long_n = n;
	len = _get_num_len(long_n);
	ptr = (char *)malloc(sizeof(char) * len + 1);
	if (!ptr)
		return (NULL);
	ptr[len] = '\0';
	if (long_n == 0)
		ptr[0] = '0';
	else if (long_n < 0)
	{
		ptr[0] = '-';
		long_n *= -1;
	}
	while (long_n > 0)
	{
		ptr[len - 1] = long_n % 10 + '0';
		long_n /= 10;
		len--;
	}
	return (ptr);
}
