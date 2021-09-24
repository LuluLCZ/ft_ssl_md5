/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   md5_ops.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucien <lucien@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/24 16:08:32 by lucien            #+#    #+#             */
/*   Updated: 2021/09/24 16:10:52 by lucien           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ssl.h"

/*
** Not working with define, trying with function
** # define F(x, y, z) ((x) & (y)) | ((~x) & (z))
** # define G(x, y, z) ((x) & (z)) | ((y) & (~z))
** # define H(x, y, z) (x) ^ (y) ^ (z)
** # define I(x, y, z) (y) ^ (x | (~z))
*/

uint32_t    F1(uint32_t buffers[]) {
        return ((buffers[1] & buffers[2]) | (~buffers[1] & buffers[3]));
}

uint32_t    G1(uint32_t buffers[]) {
        return ((buffers[1] & buffers[3]) | (~buffers[2] & buffers[3]));
}

uint32_t    H1(uint32_t buffers[]) {
        return (buffers[1] ^ buffers[2] ^ buffers[3]);
}

uint32_t    I1(uint32_t buffers[]) {
        return (buffers[2] ^ (buffers[1] | ~buffers[3]));
}
