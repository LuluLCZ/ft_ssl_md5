/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucien <lucien@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/23 10:58:50 by lucien            #+#    #+#             */
/*   Updated: 2021/09/23 17:18:03 by lucien           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ssl.h"

void    parse_stdin(t_args *args) {
    char *data;

    if (args->flags->p == TRUE || !args->real_args[0]) {
        if (!(data = read_file_content(0)))
            exit(-1);
        if (args->flags->p) {
            if (args->flags->q == FALSE) {
                ft_putstr("(\"");
                ft_putstr(ft_del_nl(data));
                ft_putstr("\") = ");
            }
            if (args->algo == 'm')
                ft_putstr(ft_md5(data, ft_strlen(data)));
            else
                ft_putstr(ft_sha_256(data, ft_strlen(data)));
            ft_putchar('\n');
        } else {
            ft_putstr("(stdin)= ");
            if (args->algo == 'm')
                ft_putstr(ft_md5(data, ft_strlen(data)));
            else 
                ft_putstr(ft_sha_256(data, ft_strlen(data)));
            ft_putchar('\n');
            free(data);
        }
    }
}

void    run_hash_s(t_args *args) {
    char *dataa;

    dataa = args->algo == 'm' ? ft_md5(args->real_args[0], ft_strlen(args->real_args[0])) : ft_sha_256(args->real_args[0], ft_strlen(args->real_args[0]));
    if (args->flags->s == TRUE) {
        if (args->flags->q == FALSE) {
            if (args->flags->r == FALSE) {
                args->algo == 'm' ? ft_putstr("MD5 (\"") : ft_putstr("SHA256 (\"");
                ft_putstr(args->real_args[0]);
                ft_putstr("\") = ");
                ft_putstr(dataa);
                ft_putchar('\n');
            }
            if (args->flags->r == TRUE && args->flags->q == FALSE) {
                ft_putstr(dataa);
                ft_putchar('"');
                ft_putstr(args->real_args[0]);
                ft_putstr("\"\n");
            }
        }
    }
    free(dataa);
}

void       process_last_args(t_args *args) {
    int i = 0;
    char    *data;

    if (args->flags->s == TRUE) i = 1;
    while (args->real_args[i]) {
        data = retrieve_content(args->real_args[i]);
        if (data == NULL) {
            ft_putstr_fd("ft_ssl: ", 2);
            ft_putstr_fd(args->algo == 'm' ? "md5: " : "sha256: ", 2);
            ft_putstr_fd(args->real_args[i], 2);
            ft_putstr_fd(": No such file or directory", 2);
        } else {
            if (args->flags->q == FALSE && args->flags->r == FALSE) {
                ft_putstr(args->algo == 'm' ? "MD5 (" : "SHA256 (");
                ft_putstr(args->real_args[i]);
                ft_putstr(") = ");
            }
            if (data != NULL)
                ft_putstr(args->algo == 'm' ? ft_md5(data, ft_strlen(data)) : ft_sha_256(data, ft_strlen(data)));
            if (args->flags->q == FALSE && args->flags->r == TRUE) {
                ft_putchar('"');
                ft_putstr(args->real_args[i]);
                ft_putstr("\"\n");
            }
        }
        free(data);
        i++;
    }
}

int	main(int ac, char **av)
{
	t_args	*args;

    if (!(args = malloc(sizeof(t_args)))) {
        exit(-1);
    }
    if (ac >= 2) {
        if (ft_strcmp(av[1], "md5") == 0)
            args->algo = 'm';
        else if (ft_strcmp(av[1], "sha256") == 0)
            args->algo = 's';
        else {
            ft_putstr_fd("ft_ssl: Error: ", 2);
            ft_putstr_fd(av[1], 2);
            ft_putstr_fd(" is an invalid command.\n\nCommands:\nmd5\nsha256\n\nFlags:\n-p -q -r -s\n", 2);
            exit (-1);
        }
        args = check_arg(ac, av, args);
        parse_stdin(args);
        if (args->flags->s == TRUE)
            run_hash_s(args);
        process_last_args(args);
    }
	return (0);
}
