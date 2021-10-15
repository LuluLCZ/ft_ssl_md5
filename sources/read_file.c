/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucien <lucien@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/20 11:26:54 by lucien            #+#    #+#             */
/*   Updated: 2021/10/15 14:15:12 by lucien           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/init.h"

char    *read_file_content(int fd) {
    char    *str;
    char    *file_data;
    int     len;
    int     i = 0;
    char    buff[1000000];

    if (!(file_data = (char *)malloc(sizeof(char) * 1000000000))) {
        ft_putstr_fd("Erreur lors de l'allocation mémoire", 2);
        return (NULL);
    }
    ft_bzero(file_data, sizeof(file_data) * 10);
    while ((len = read(fd, buff, 1000000)) > 0) {
        if (!(str = malloc(1000000))) {
            ft_putstr_fd("Erreur lors de l'allocation mémoire", 2);
            return (NULL);
        }
        ft_bzero(str, sizeof(str) * 10000);
        str = ft_strncpy(str, buff, len);
        write(1, str, ft_strlen(str));
        if (i > 0)
        {
            file_data = realloc(file_data, i + 1000000);
            ft_memmove(file_data + i, str, len);
            free(str);
        } else {
            file_data = ft_strncpy(file_data, str, len);
            free(str);
        }
        i += len;
    }
    // write(1, (file_data), ft_strlen(file_data));
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
    {
        // free(data);
        return (NULL);
    }
    if (close(fd) < 0)
        return (NULL);
    return (data);
}
