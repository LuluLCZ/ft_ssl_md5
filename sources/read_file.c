/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucien <lucien@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/20 11:26:54 by lucien            #+#    #+#             */
/*   Updated: 2021/09/26 15:35:32 by lucien           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/init.h"

char    *read_file_content(int fd) {
    char    *str;
    char    *file_data;
    int     len;
    int     i = 0;
    char    buff[10];

    if (!(file_data = (char *)malloc(sizeof(char) * 10))) {
        ft_putstr_fd("Erreur lors de l'allocation mémoire", 2);
        return (NULL);
    }
    ft_bzero(file_data, sizeof(file_data));
    while ((len = read(fd, buff, 10)) > 0) {
        if (!(str = malloc(10))) {
            ft_putstr_fd("Erreur lors de l'allocation mémoire", 2);
            return (NULL);
        }
        ft_memmove(str, buff, len);
        if (i > 0)
        {
            file_data = realloc(file_data, i + 10);
            ft_memmove(file_data + i, str, len);
        } else {
            file_data = ft_strncpy(file_data, str, len);
            free(str);
        }
        i += len;
    }
    if (len < 0) {
        ft_putstr_fd("Erreur lors de la lecture du fichier", 2);
        return (NULL);
    }
    return (file_data);
}

char    *retrieve_content(char *filename) {
    int     fd;
    char    *data;

    if ((fd = open(filename, O_RDONLY)) < 0)
        return (NULL);
    if (!(data = read_file_content(fd)))
        return (NULL);
    if (close(fd) < 0)
        return (NULL);
    return (data);
}
