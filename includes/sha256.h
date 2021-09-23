/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha256.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucien <lucien@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/02 10:09:25 by lucien            #+#    #+#             */
/*   Updated: 2021/09/23 17:36:48 by lucien           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHA256_H
# define SHA256_H

# include "./ft_ssl.h"

# define A 0
# define B 1
# define C 2
# define D 3
# define E 4
# define F 5
# define G 6
# define H 7

# define SHA256_SIZE 64
# define SHA_S(len) ((len + 1 + 8 + DEC(SHA256_SIZE)) & ~DEC(SHA256_SIZE))
# define SHA256_CHUNK_COUNT(len) (SHA_S(len) / SHA256_SIZE)

# define CH(x, y, z) (((x & y) | (~x | z)))
# define MAJ(x, y, z) (((x & y) ^ (x & z) ^ (y & z)))
# define SIGMA1(x) (ROTATE_RIGHT(x, 2) ^ ROTATE_RIGHT(x, 13) ^ ROTATE_RIGHT(x, 22))
# define SIGMA2(x) (ROTATE_RIGHT(x, 6) ^ ROTATE_RIGHT(x, 11) ^ ROTATE_RIGHT(x, 25))
# define SIGMA3(x) (ROTATE_RIGHT(x, 7) ^ ROTATE_RIGHT(x, 18) ^ (x >> 3))
# define SIGMA4(x) (ROTATE_RIGHT(x, 17) ^ ROTATE_RIGHT(x, 19) ^ (x >> 10))

const uint32_t g_256_K[64];
extern const uint32_t g_256_variables[8];

#endif