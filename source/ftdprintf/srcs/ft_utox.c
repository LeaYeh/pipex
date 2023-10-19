/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utox.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lyeh <lyeh@student.42vienna.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 17:51:38 by lyeh              #+#    #+#             */
/*   Updated: 2023/10/19 17:16:51 by lyeh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_utils.h"

int	_get_num_len(unsigned long int nbr, int base)
{
	int	i;

	i = 0;
	if (nbr == 0)
		return (1);
	while (nbr)
	{
		nbr /= base;
		i++;
	}
	return (i);
}

char	*ft_utox(unsigned long int nbr, bool is_upper)
{
	char					*ret;
	char					*tab;
	int						i;
	int						len;
	unsigned long long int	tmp;

	len = _get_num_len(nbr, 16);
	ret = (char *)malloc(sizeof(char) * (len + 1));
	if (!ret)
		return (NULL);
	tab = "0123456789abcdef";
	if (is_upper)
		tab = "0123456789ABCDEF";
	i = 0;
	while (i < len)
	{
		tmp = ft_pow(16, len - (i + 1));
		ret[i] = tab[(nbr / tmp)];
		nbr = nbr % tmp;
		i += 1;
	}
	ret[i] = '\0';
	return (ret);
}
