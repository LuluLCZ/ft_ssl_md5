/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucien <lucien@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/23 10:58:50 by lucien            #+#    #+#             */
/*   Updated: 2021/10/15 14:02:40 by lucien           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ssl.h"

void    parse_stdin(t_args *args) {
    char *data;
    char *result;

    if (args->flags->p == TRUE || !args->real_args[0]) {
        if (!(data = read_file_content(0)))
            exit(-1);
        if (args->flags->p) {
            if (args->flags->q == FALSE && args->flags->r == FALSE) {
                ft_putstr("(\"");
                result = ft_del_nl(data);
                ft_putstr(result);
                free(result);
                ft_putstr("\") = ");
            }
            if (args->algo == 'm') {
                result = ft_md5(data, ft_strlen(data));
                ft_putstr(result);
                free(result);
            }
            else {
                result = ft_sha_256(data, ft_strlen(data));
                ft_putstr(result);
                free(result);
            }
            if (args->flags->q == FALSE && args->flags->r == TRUE) {
                ft_putstr(" (\"");
                result = ft_del_nl(data);
                ft_putstr(result);
                ft_putstr("\")");
                free(result);
            }
            free(data);
            ft_putchar('\n');
        } else {
            ft_putstr("(stdin)= ");
            if (args->algo == 'm') {
                result = ft_md5(data, ft_strlen(data));
                ft_putstr(result);
                free(result);
            }
            else  {
                result = ft_sha_256(data, ft_strlen(data));
                ft_putstr(result);
                free(result);
            }
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
                ft_putstr(" \"");
                ft_putstr(args->real_args[0]);
                ft_putstr("\"\n");
            }
        } else {
            ft_putstr(dataa);
            ft_putchar('\n');
        }
    }
    free(dataa);
}

void       process_last_args(t_args *args, char *arg, int i, char **av) {
    char    *data;
    char    *result;

    data = retrieve_content(arg);
    if (data == NULL) {
        ft_putstr_fd("ft_ssl: ", 2);
        ft_putstr_fd(args->algo == 'm' ? "md5: " : "sha256: ", 2);
        ft_putstr_fd(args->real_args[i], 2);
        ft_putstr_fd(": No such file or directory\n", 2);
    } else {
        if (ft_strcmp(av[1], "md5") == 0) {
            result = ft_md5(data, ft_strlen(data));
        } else {
            result = ft_sha_256(data, ft_strlen(data));
        }
        if (args->flags->q == FALSE && args->flags->r == FALSE) {
            ft_putstr(args->algo == 'm' ? "MD5 (" : "SHA256 (");
            ft_putstr(args->real_args[i]);
            ft_putstr(") = ");
        }
        ft_putstr(result);
        if (args->flags->q == FALSE && args->flags->r == TRUE) {
            ft_putstr(" \"");
            ft_putstr(args->real_args[i]);
            ft_putstr("\"");
        }
        ft_putstr("\n");
        free(result);
    }
    free(data);
}

int	main(int ac, char **av)
{
	t_args	*args;
    int     i = 0;

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
        if (args->flags->p || !args->real_args[0])
            parse_stdin(args);
        if (args->flags->s == TRUE)
            run_hash_s(args);
        if (args->flags->s == TRUE)
            i = 1;
        while (args->real_args[i]) {
            if ((args->flags->s == FALSE && args->real_args[0]) || (args->flags->s == TRUE && args->real_args[1]))
                process_last_args(args, args->real_args[i], i, av);
            i++;
        }
        // sleep(500);
    }
	return (0);
}
