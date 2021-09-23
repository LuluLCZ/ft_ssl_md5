/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucien <lucien@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/20 11:26:54 by lucien            #+#    #+#             */
/*   Updated: 2021/09/23 17:24:58 by lucien           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/init.h"

char    *read_file_content(int fd) {
    char    *str;
    char    *file_data_tmp;
    char    *file_data;
    // char *new;
    int     len;
    char    buff[100000];

    if (!(file_data = malloc(sizeof(file_data)))) {
        ft_putstr_fd("Erreur lors de l'allocation mémoire", 2);
        return (NULL);
    }
    ft_bzero(file_data, sizeof(file_data));
    while ((len = read(fd, buff, 100000)) > 0) {
        if (!(str = (char *)malloc(sizeof(char) * 10))) {
            ft_putstr_fd("Erreur lors de l'allocation mémoire", 2);
            return (NULL);
        }
        ft_memmove(str, buff, len);
        if (ft_strlen(file_data) > 0)
        {
            file_data_tmp = realloc(file_data, ft_strlen(file_data) + 100000);
            file_data = ft_strjoin_free(file_data_tmp, str);

        } else {
            file_data = ft_strdup_size(str, ft_strlen(str));
            free(str);
        }
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
    // char    *error;

    if ((fd = open(filename, O_RDONLY)) < 0) {
        // error = ft_strjoin(filename, ": No such file or directory");
        // write(2, error, ft_strlen(error));
        // free(error);
        return (NULL);
    }
    if (!(data = read_file_content(fd)))
        return (NULL);
    if (close(fd) < 0) {
        // error = ft_strjoin("Impossible de fermer le fichier ", filename);
        // write(2, error, ft_strlen(error));
        // free(error);
        return (NULL);
    }

    return (data);
}
