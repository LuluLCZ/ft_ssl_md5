/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucien <lucien@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/31 14:36:48 by lucien            #+#    #+#             */
/*   Updated: 2021/09/30 09:59:01 by lucien           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ssl.h"
#include "../includes/md5.h"

unsigned char	*build_msg(const char *msg, size_t msg_len, size_t
							formatted_msg_len, t_bool is_little_endian)
{
	unsigned char	*formatted_msg;
	size_t			cursor;

	if (!(formatted_msg = malloc(formatted_msg_len)))
		return (NULL);
	ft_memcpy(formatted_msg, msg, msg_len);
	formatted_msg[msg_len] = 0b10000000;
	cursor = msg_len + 1;
	while (cursor < formatted_msg_len)
		formatted_msg[cursor++] = 0;
	*(uint64_t *)(formatted_msg + cursor - 8) = \
		is_little_endian ? 8 * msg_len : ft_bswap_uint64(8 * msg_len);
	return (formatted_msg);
}

char	*build_hash(uint32_t *buffers, size_t buffer_count, \
		t_bool is_little_endian)
{
	char		*hash;
	char		*tmp_hash;
	size_t		buffer_i;
	uint32_t	buffer;
	

	buffer_i = 0;
	if (!(hash = ft_strnew(buffer_count * 8)))
		return (NULL);
	while (buffer_i < buffer_count) 
	{
		buffer = is_little_endian ? ft_bswap_uint32(buffers[buffer_i]) : buffers[buffer_i];
		if (!(tmp_hash = ft_itoa_b(buffer, 16, 'a', 8)))
			return (NULL);
		ft_strncpy(hash + (buffer_i * 8), tmp_hash, 8);
		free(tmp_hash);
		buffer_i++;
	}
	return (hash);
}
