/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_max.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lyeh <lyeh@student.42vienna.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 17:34:58 by lyeh              #+#    #+#             */
/*   Updated: 2023/10/25 14:05:34 by lyeh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_max(int count, ...)
{
	va_list	args;
	int		max_int;
	int		cur_num;

	max_int = INT_MIN;
	va_start(args, count);
	while (count-- > 0)
	{
		cur_num = va_arg(args, int);
		if (cur_num > max_int)
			max_int = cur_num;
	}
	return (max_int);
}
