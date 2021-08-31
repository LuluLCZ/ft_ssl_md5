/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucien <lucien@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/30 11:46:23 by lucien            #+#    #+#             */
/*   Updated: 2021/08/31 09:49:06 by lucien           ###   ########.fr       */
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

typedef enum	e_bool {
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



#endif