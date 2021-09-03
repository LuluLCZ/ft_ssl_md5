/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucien <lucien@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/30 11:46:23 by lucien            #+#    #+#             */
/*   Updated: 2021/09/03 09:39:57 by lucien           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SSL_H
# define FT_SSL_H
# include <stdio.h>
# include "../libft/includes/libft.h"
# include <unistd.h>

# define ROTATE_LEFT(x, n) (((x) << (n)) | ((x) >> (32-(n))))
# define ROTATE_RIGHT(x, n) (((x) >> (n)) | ((x) << (32-(n))))
# define ROTATE_RIGHT_64(x, n) (((x) >> (n)) | ((x) << (64-(n))))

# define DEC(x) (x - 1)


typedef enum e_bool
{
	FALSE,
	TRUE
}				t_bool;

typedef uint32_t	t_4_uint32[4];
typedef uint32_t	t_8_uint32[8];
typedef uint64_t	t_8_uint64[8];
typedef uint32_t	t_16_uint32[16];
typedef uint32_t	t_64_uint32[64];
typedef uint64_t	t_80_uint32[80];
typedef uint64_t	t_80_uint64[80];

char			*ft_uitoa_base_len(uintmax_t nb, intmax_t base, \
					char letter, size_t len);
uint64_t		ft_bswap_uint64(uint64_t x);
uint32_t		ft_bswap_uint32(uint32_t x);
void			ft_uint64_arr_assign_add(uint64_t *dst, \
		const uint64_t *src, size_t len);
void			ft_uint32_arr_assign_add(uint32_t *dst, \
		const uint32_t *src, size_t len);
unsigned char	*build_msg(const char *msg, size_t msg_len, size_t \
							formatted_msg_len, t_bool is_little_endian);
char			*build_hash(uint32_t *buffers, size_t buffer_count, \
		t_bool is_little_endian);
char			*build_hash_64(uint64_t *buffers, size_t buffer_count, \
		t_bool is_little_endian);
void	ft_copy_to_buffer(uint32_t *dst, \
				const uint32_t *src, size_t len);
void	ft_copy_to_buffer(uint32_t *dst, \
				const uint32_t *src, size_t len);

#endif