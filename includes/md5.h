/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   md5.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucien <lucien@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/30 13:53:02 by lucien            #+#    #+#             */
/*   Updated: 2021/08/31 14:41:59 by lucien           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MD5_H
# define MD5_H

# include "./ft_ssl.h"

# define DEC(x) (x - 1)

/* Chunks of 512 bits */
# define MD5_CHUNK_SIZE 64

/* +1 append for the append '1' */
/* +8 for the size in 64 bits */
# define MD5_S(len) ((len + 1 + 8 + DEC(MD5_CHUNK_SIZE)) & ~DEC(MD5_CHUNK_SIZE))
# define MD5_CHUNK_COUNT(len) (MD5_S(len) / MD5_CHUNK_SIZE)

/* F, G and H are basic MD5 functions: selection, majority, parity */
# define F(x, y, z) ((x) & (y)) | ((~x) & (z))
# define G(x, y, z) ((x) & (z)) | ((y) & (~z))
# define H(x, y, z) (x) ^ (y) ^ (z)
# define I(x, y, z) (y) ^ (x | (~z))

# define A 0
# define B 1
# define C 2
# define D 3

extern const uint32_t   g_variables;
const uint32_t          g_S[64];
const uint32_t          g_K[64];

#endif
