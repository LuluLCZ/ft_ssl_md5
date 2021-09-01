/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   first_steps.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucien <lucien@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/30 11:46:12 by lucien            #+#    #+#             */
/*   Updated: 2021/08/31 15:47:08 by lucien           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/md5.h"

void	ft_copy_to_buffer(uint32_t *dst, \
				const uint32_t *src, size_t len)
{
	size_t		index;

	index = 0;
	while (index < len)
	{
		dst[index] = src[index];
		index++;
	}
}

static void	md5_shuffle(uint32_t f, uint32_t g, t_4_uint32 tmp_buff, \
			size_t chunk_cursor, t_16_uint32 chunk)
{
	f += tmp_buff[A] + g_K[chunk_cursor] + chunk[g];
	tmp_buff[A] = tmp_buff[D];
	tmp_buff[D] = tmp_buff[C];
	tmp_buff[C] = tmp_buff[B];
	tmp_buff[B] = tmp_buff[B] + ROTATE_LEFT(f, g_S[chunk_cursor]);
}

static void	md5_process(size_t chunk_cursor, t_4_uint32 tmp_buff, \
			t_16_uint32 chunk)
{
	uint32_t		g;
	uint32_t		f;

	if (chunk_cursor < 16)
	{
		f = F(tmp_buff[B], tmp_buff[C], tmp_buff[D]);
		g = chunk_cursor;
	}
	else if (chunk_cursor < 32)
	{
		f = G(tmp_buff[B], tmp_buff[C], tmp_buff[D]);
		g = (5 * chunk_cursor + 1) % 16;
	}
	else if (chunk_cursor < 48)
	{
		f = H(tmp_buff[B], tmp_buff[C], tmp_buff[D]);
		g = (3 * chunk_cursor + 5) % 16;
	}
	else
	{
		f = I(tmp_buff[B], tmp_buff[C], tmp_buff[D]);
		g = (7 * chunk_cursor) % 16;
	}
	md5_shuffle(f, g, tmp_buff, chunk_cursor, chunk);
}

static void	md5_form_buffer(unsigned char *padded_msg, \
			size_t msg_len, t_4_uint32 buffers)
{
	size_t			chunk_i;
	size_t			chunk_cursor;
	t_16_uint32		chunk;
	t_4_uint32		tmp_buff;

	chunk_i = 0;
	chunk_cursor = 0;
	ft_copy_to_buffer(buffers, &g_variables, 4);
	while (chunk_i < MD5_CHUNK_COUNT(msg_len))
	{
		ft_memcpy(chunk, padded_msg + chunk_i * MD5_CHUNK_SIZE,
			MD5_CHUNK_SIZE);
		chunk_cursor = -1;
		ft_copy_to_buffer(tmp_buff, buffers, 4);
		while (++chunk_cursor < MD5_CHUNK_SIZE)
			md5_process(chunk_cursor, tmp_buff, chunk);
		ft_uint32_arr_assign_add(buffers, tmp_buff, 4);
		chunk_i++;
	}
}

char	*ft_md5(const char *msg, size_t msg_len)
{
	t_4_uint32		buffers;
	unsigned char	*padded_msg;

	padded_msg = build_msg(msg, msg_len, MD5_CHUNK_COUNT(msg_len) * \
		MD5_CHUNK_SIZE, TRUE);
	if (!padded_msg)
		return (NULL);
	md5_form_buffer(padded_msg, msg_len, buffers);
	return (build_hash(buffers, 4, TRUE));
}

int	main(int ac, char **av)
{
	char	*test;

	if (ac < 0)
	{
		write(1, "nop", 3);
	}
	test = ft_strdup(av[1]);
	printf("\n%s", ft_md5(test, ft_strlen(test)));
	return (0);
}
