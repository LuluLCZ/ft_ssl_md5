/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   itoa_base.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucien <lucien@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/31 14:28:17 by lucien            #+#    #+#             */
/*   Updated: 2021/09/24 16:35:37 by lucien           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/md5.h"
#include "../includes/ft_ssl.h"

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