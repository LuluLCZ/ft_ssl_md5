/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_del_nl.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucien <lucien@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/23 12:04:23 by lucien            #+#    #+#             */
/*   Updated: 2021/09/30 09:55:27 by lucien           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

char    *ft_del_nl(char *s1) {
    int i = 0;
    int j = 0;
    char *dst;

    if (!s1) {
        return NULL;
    }
    if (!(dst = malloc(sizeof(char) * ft_strlen(s1))))
        return (NULL);
    while (s1[i]) {
        if (s1[i] != '\n') {
            dst[j] = s1[i];
            j++;
        }
        i++;
    }
    dst[j] = '\0';
    // free(s1);
    return (dst);
}