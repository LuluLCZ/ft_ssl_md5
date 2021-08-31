/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   swap.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucien <lucien@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/31 14:29:11 by lucien            #+#    #+#             */
/*   Updated: 2021/08/31 14:32:46 by lucien           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ssl.h"
#include "../includes/md5.h"

uint64_t	ft_bswap_uint64(uint64_t x)
{
	x = ((x << 8) & 0xFF00FF00FF00FF00ULL)
		| ((x >> 8) & 0x00FF00FF00FF00FFULL);
	x = ((x << 16) & 0xFFFF0000FFFF0000ULL)
		| ((x >> 16) & 0x0000FFFF0000FFFFULL);
	return ((x << 32) | (x >> 32));
}

uint32_t	ft_bswap_uint32(uint32_t x)
{
	x = ((x << 8) & 0xFF00FF00) | ((x >> 8) & 0xFF00FF);
	return ((x << 16) | (x >> 16));
}

void	ft_uint64_arr_assign_add(uint64_t *dst, const uint64_t *src, size_t len)
{
	size_t	i;

	i = 0;
	while (i < len)
	{
		dst[i] += src[i];
		i++;
	}
}

void	ft_uint32_arr_assign_add(uint32_t *dst,
		const uint32_t *src, size_t len)
{
	size_t	i;

	i = 0;
	while (i < len)
	{
		dst[i] += src[i];
		i++;
	}
}
