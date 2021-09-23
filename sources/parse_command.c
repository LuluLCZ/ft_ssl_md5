/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucien <lucien@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/21 08:28:50 by lucien            #+#    #+#             */
/*   Updated: 2021/09/23 16:14:43 by lucien           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ssl.h"

static void        set_flag(char c, t_args *args) {
    if (c == 'p')
        args->flags->p = TRUE;
    else if (c == 'q')
        args->flags->q = TRUE;
    else if (c == 'r')
        args->flags->r = TRUE;
    else if (c == 's')
        args->flags->s = TRUE;
    else {
        ft_putstr_fd("ft_ssl: Error: -", 2);
        ft_putchar_fd(c, 2);
        ft_putstr_fd(" is an invalid flag\n\nCommands: md5\nsha256\n\nFlags:\n-p -q -r -s\n", 2);
        exit(-1);
    }
}

t_args        *check_arg(int ac, char **av, t_args *args) {
    int     i;
    int     j;
    int     to_skip = 0;
    int     done = 0;

    i = 2;
    j = 0;
    if (!(args->flags = malloc(sizeof(t_flags)))) {
        exit (-1);
    }
    if (!(args->real_args = (char **)malloc(sizeof(char *) * 10000))) {
        exit(-1);
    }
    while (i < ac && av[i]) {
        if (av[i][0] == '-' && done == 0) {
            /*
            ** Check if there is more than one flag for one argument
            */
            if (ft_strlen(av[i]) > 2) {
                ft_putstr_fd("ft_ssl: Error: You need to use flags separately. -p -q -r -s", 2);
                exit(-1);
            }
            set_flag(av[i][1], args);
            to_skip++;
            args->args_to_jump = to_skip;
        } else {
            done = 1;
            args->real_args[j] = ft_strdup(av[i]);
            j++;
        }
        i++;
    }
    return (args)
;}