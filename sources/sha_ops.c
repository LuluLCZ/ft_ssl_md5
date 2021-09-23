/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha_ops.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucien <lucien@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/23 17:33:17 by lucien            #+#    #+#             */
/*   Updated: 2021/09/23 18:03:44 by lucien           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ssl.h"


uint32_t	sha256_op_ch(uint32_t x, uint32_t y, uint32_t z)
{
	return ((x & y) ^ (~x & z));
}

uint32_t	sha256_op_maj(uint32_t x, uint32_t y, uint32_t z)
{
	return ((x & y) ^ (x & z) ^ (y & z));
}

uint32_t	sha256_op_a(uint32_t x)
{
	return (ft_brotate_right(x,
		2) ^ ft_brotate_right(x, 13) ^ ft_brotate_right(x, 22));
}

uint32_t	sha256_op_b(uint32_t x)
{
	return (ft_brotate_right(x,
		6) ^ ft_brotate_right(x, 11) ^ ft_brotate_right(x, 25));
}

uint32_t	sha256_op_c(uint32_t x)
{
	return (ft_brotate_right(x,
		7) ^ ft_brotate_right(x, 18) ^ (x >> 3));
}

uint32_t	sha256_op_d(uint32_t x)
{
	return (ft_brotate_right(x,
		17) ^ ft_brotate_right(x, 19) ^ (x >> 10));
}

uint32_t	ft_brotate_right(uint32_t x, char rotations)
{
	return ((x >> rotations) | (x << (32 - rotations)));
}
