/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_toupper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lyeh <lyeh@student.42vienna.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 11:43:10 by lyeh              #+#    #+#             */
/*   Updated: 2023/09/10 13:37:45 by lyeh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// lower case and upper case is only different on the 5th bit
// 0xffdf = 1111111111011111
int	ft_toupper(int c)
{
	if (ft_isalpha(c))
		return (c & 0xffdf);
	return (c);
}
