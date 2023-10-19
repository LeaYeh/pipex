/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lyeh <lyeh@student.42vienna.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 15:52:47 by lyeh              #+#    #+#             */
/*   Updated: 2023/10/19 17:17:36 by lyeh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_utils.h"

int	ft_in_substr(const char c, const char *sub)
{
	int	i;

	i = 0;
	while (sub[i])
	{
		if (sub[i] == c)
			return (true);
		i++;
	}
	return (false);
}

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

int	ft_min(int count, ...)
{
	va_list	args;
	int		min_int;
	int		cur_num;

	min_int = INT_MAX;
	va_start(args, count);
	while (count-- > 0)
	{
		cur_num = va_arg(args, int);
		if (cur_num < min_int)
			min_int = cur_num;
	}
	return (min_int);
}

long long int	ft_pow(int base, int n)
{
	long long int	ret;

	ret = 1;
	while (n > 0)
	{
		ret *= base;
		n--;
	}
	return (ret);
}
