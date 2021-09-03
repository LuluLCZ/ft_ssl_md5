/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha256.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucien <lucien@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/02 10:09:09 by lucien            #+#    #+#             */
/*   Updated: 2021/09/03 09:59:14 by lucien           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/sha256.h"

void	sha256_process_1(t_8_uint32 tmp_buff, t_64_uint32 chunk)
{
	int	t;
	uint32_t	temp1;
	uint32_t	temp2;

	t = 0;
	while (t < 64) {
		temp1 = tmp_buff[H] + SIGMA2(tmp_buff[E]) + CH(tmp_buff[E], tmp_buff[F], tmp_buff[G]) + g_256_K[t] + chunk[t];
		temp2 = SIGMA1(tmp_buff[A]) + MAJ(tmp_buff[A], tmp_buff[B], tmp_buff[C]);
		tmp_buff[H] = tmp_buff[G];
		tmp_buff[G] = tmp_buff[F];
		tmp_buff[F] = tmp_buff[E];
		tmp_buff[E] = tmp_buff[D] + temp1;
		tmp_buff[D] = tmp_buff[C];
		tmp_buff[C] = tmp_buff[B];
		tmp_buff[B] = tmp_buff[A];
		tmp_buff[A] = temp1 + temp2;
		t++;
	}
}

static void	sha256_form_buffer(unsigned char *padded_msg, \
			size_t msg_len, t_8_uint32	buffers)
{
	size_t		chunk_i;
	t_64_uint32	chunk;
	t_8_uint32	tmp_buff;
	int			i;

	chunk_i = 0;
	ft_copy_to_buffer(buffers, g_256_variables, 8);
	i = 0;
	while (chunk_i < SHA256_CHUNK_COUNT(msg_len))
	{
		while (i < 64) {
			if (i < 16)
				chunk[i] = ft_bswap_uint32(((uint32_t *)padded_msg)[i]);
			else
				chunk[i] = chunk[i - 16] + SIGMA3(chunk[i - 15]) + chunk[i - 7] + SIGMA4(chunk[i - 2]);
			i++;
		}
		ft_copy_to_buffer(tmp_buff, buffers, 8);
		sha256_process_1(tmp_buff, chunk);
		ft_uint32_arr_assign_add(buffers, tmp_buff, 8);
		chunk_i++;
	}
}

char	*ft_sha_256(const char *msg, size_t msg_len) {
	unsigned char	*padded_msg;
	t_8_uint32		buffers;

	if (!(padded_msg = build_msg(msg, msg_len, SHA256_CHUNK_COUNT(msg_len) * \
		SHA256_SIZE, FALSE)))
		return (NULL);
	sha256_form_buffer(padded_msg, msg_len, buffers);
	return (build_hash(buffers, 8, FALSE));
}

int	main(int ac, char **av)
{
	char	*test;

	if (ac < 0)
	{
		write(1, "nop", 3);
	}
	test = ft_strdup(av[1]);
	printf("\n%s", ft_sha_256(test, ft_strlen(test)));
	return (0);
}