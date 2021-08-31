/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   first_steps.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucien <lucien@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/30 11:46:12 by lucien            #+#    #+#             */
/*   Updated: 2021/08/31 10:12:36 by lucien           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ssl.h"
#include "../includes/md5.h"

char	*ft_uitoa_base(uintmax_t nb, intmax_t base, char letter)
{
	uintmax_t	temp;
	int			power;
	char		*str;

	temp = nb;
	power = 1;
	while (temp /= base)
		power++;
	if (!(str = ft_strnew(power)))
		return (NULL);
	while (power--)
	{
		if (nb % base >= 10)
			str[power] = nb % base - 10 + letter;
		else
			str[power] = nb % base + '0';
		nb /= base;
	}
	return (str);
}

char	*ft_uitoa_base_len(uintmax_t nb, intmax_t base, char letter, size_t len)
{
	int		i;
	int		diff;
	char	*str;
	char	*new_str;

	i = 0;
	str = ft_uitoa_base(nb, base, letter);
	diff = len - ft_strlen(str);
	if (diff > 0)
	{
		if (!(new_str = ft_strnew(len)))
			return (NULL);
		while (i < diff)
			new_str[i++] = '0';
		ft_strncpy(new_str + i, str, len - diff);
		free(str);
		return (new_str);
	}
	return (str);
}

uint64_t		ft_bswap_uint64(uint64_t x)
{
	x = ((x << 8) & 0xFF00FF00FF00FF00ULL)
		| ((x >> 8) & 0x00FF00FF00FF00FFULL);
	x = ((x << 16) & 0xFFFF0000FFFF0000ULL)
		| ((x >> 16) & 0x0000FFFF0000FFFFULL);
	return ((x << 32) | (x >> 32));
}

uint32_t		ft_bswap_uint32(uint32_t x)
{
	x = ((x << 8) & 0xFF00FF00) | ((x >> 8) & 0xFF00FF00);
	return ((x << 16) | (x >> 16));
}

void	ft_uint64_arr_assign_add(uint64_t *dst, const uint64_t *src, size_t len)
{
	size_t i;

	i = 0;
	while (i < len)
	{
		dst[i] += src[i];
		i++;
	}
}

void	ft_uint32_arr_assign_add(uint32_t *dst, const uint32_t *src, size_t len)
{
	size_t i;

	i = 0;
	while (i < len)
	{
		dst[i] += src[i];
		i++;
	}
}

unsigned char	build_msg(const char msg, size_t msg_len, size_t
							formatted_msg_len, t_bool is_little_endian)
{
	unsigned char	*formatted_msg;
	size_t			cursor;

	// formatted_msg_len is the size of the expected formatted message
	if (!(formatted_msg = malloc(formatted_msg_len)))
		return (NULL);
	ft_memcpy(formatted_msg, msg, msg_len);
	formatted_msg[msg_len] = 0b10000000;
	cursor = msg_len + 1;
	while (cursor < formatted_msg_len)
		formatted_msg[cursor++] = 0;
	*(uint64_t *)(formatted_msg + cursor - 8) =
		is_little_endian ? 8 * msg_len : ft_bswap_uint64(8 * msg_len);
	return (formatted_msg);
}

void			ft_copy_to_buffer(uint32_t *dst, const uint32_t *src, size_t len)
{
	size_t		index;

	while (index < len)
	{
		dst[index] = src[index];
		index++;
	}
}

char			*build_hash(uint32_t *buffers, size_t buffer_count, t_bool is_little_endian)
{
	char		*hash;
	char		*tmp_hash;
	size_t		buffer_i;
	uint32_t	buffer;

	buffer_i = 0;
	if (!(hash = ft_strnew(buffer_count * 8)))
		return (NULL);
	
	while (buffer_i < buffer_count) {
		buffer = is_little_endian ? ft_bswap_uint32(buffers[buffer_i]) : buffers[buffer_i];
		if (!(tmp_hash = ft_uitoa_base_len(buffer, 16, 'a', 8)))
			return (NULL);
		ft_strncpy(hash + (buffer_i * 8), tmp_hash, 8);
		free(tmp_hash);
		buffer_i++;
	}
	return (hash);
}

char			*ft_md5(const char *msg, size_t msg_len)
{
	unsigned char	*padded_msg;
	uint32_t		buffers;
	size_t			chunk_i;
	size_t			chunk_cursor;
	uint32_t		*chunk;
	uint32_t		*tmp_buff;
	uint32_t		g;
	uint32_t		f;

	if (!(padded_msg = build_msg(
				msg, msg_len, MD5_CHUNK_COUNT(msg_len) * MD5_CHUNK_SIZE, TRUE)))
		return (NULL);
	chunk_i = 0;
	chunk_cursor = 0;
	ft_copy_to_buffer(buffers, g_variables, 4);
	while (chunk_i < MD5_CHUNK_COUNT(msg_len)) {
		ft_memcpy(chunk, padded_msg + chunk_i * MD5_CHUNK_SIZE,
			MD5_CHUNK_SIZE);
		chunk_cursor = 0;
		ft_copy_to_buffer(tmp_buff, buffers, 4);
		while (chunk_cursor < MD5_CHUNK_SIZE)
		{
			if (chunk_cursor <= 15)
			{
				f = F(tmp_buff[B], tmp_buff[C], tmp_buff[D]);
				g = chunk_cursor;
			}
			else if (16 <= chunk_cursor <= 31)
			{
				f = G(tmp_buff[B], tmp_buff[C], tmp_buff[D]);
				g = (5 * chunk_cursor + 1) % 16;
			}
			else if (32 <= chunk_cursor <= 47)
			{
				f = H(tmp_buff[B], tmp_buff[C], tmp_buff[D]);
				g = (3 * chunk_cursor + 5) % 16;
			}
			else if (48 <= chunk_cursor <= 63)
			{
				f = I(tmp_buff[B], tmp_buff[C], tmp_buff[D]);
				g = (7 * chunk_cursor) % 16;
			}
			f = f + tmp_buff[A] + g_K[chunk_cursor] + chunk[g];
			tmp_buff[A] = tmp_buff[D];
			tmp_buff[D] = tmp_buff[C];
			tmp_buff[C] = tmp_buff[B];
			tmp_buff[B] = tmp_buff[B] + ROTATE_LEFT(f, g_S[chunk_cursor]);
		}
		ft_uint32_arr_assign_add(buffers, tmp_buff, 4);
		chunk_i++;
	}
	printf("%s", build_hash(buffers, 4, TRUE));
	return (build_hash(buffers, 4, TRUE));
}

int main(int ac, char **av) {
	(void)ac, av;
	char	*test;

	test = ft_strdup("test");
	ft_md5(test, ft_strlen(test));
	return (0);
}
