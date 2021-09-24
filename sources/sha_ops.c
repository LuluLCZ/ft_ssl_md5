/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha_ops.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucien <lucien@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/23 17:33:17 by lucien            #+#    #+#             */
/*   Updated: 2021/09/24 16:17:24 by lucien           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ssl.h"


/*
** Not working with define, trying with functions
** # define CH(x, y, z) (((x & y) | (~x | z)))
** # define MAJ(x, y, z) (((x & y) ^ (x & z) ^ (y & z)))
** # define SIGMA1(x) (ROTATE_RIGHT(x, 2) ^ ROTATE_RIGHT(x, 13) ^ ROTATE_RIGHT(x, 22))
** # define SIGMA2(x) (ROTATE_RIGHT(x, 6) ^ ROTATE_RIGHT(x, 11) ^ ROTATE_RIGHT(x, 25))
** # define SIGMA3(x) (ROTATE_RIGHT(x, 7) ^ ROTATE_RIGHT(x, 18) ^ (x >> 3))
** # define SIGMA4(x) (ROTATE_RIGHT(x, 17) ^ ROTATE_RIGHT(x, 19) ^ (x >> 10))
*/

uint32_t	ch(uint32_t x, uint32_t y, uint32_t z)
{
	return ((x & y) ^ (~x & z));
}

uint32_t	maj(uint32_t x, uint32_t y, uint32_t z) {
	return ((x & y) ^ (x & z) ^ (y & z));
}

uint32_t	sigma_1(uint32_t x)
{
	return (ft_brotate_right(x, 2) ^ ft_brotate_right(x, 13) ^ ft_brotate_right(x, 22));
}

uint32_t	sigma_2(uint32_t x)
{
	return (ft_brotate_right(x, 6) ^ ft_brotate_right(x, 11) ^ ft_brotate_right(x, 25));
}

uint32_t	sigma_3(uint32_t x)
{
	return (ft_brotate_right(x, 7) ^ ft_brotate_right(x, 18) ^ (x >> 3));
}

uint32_t	sigma_4(uint32_t x)
{
	return (ft_brotate_right(x, 17) ^ ft_brotate_right(x, 19) ^ (x >> 10));
}

uint32_t	ft_brotate_right(uint32_t x, char rotations)
{
	return ((x >> rotations) | (x << (32 - rotations)));
}
