# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lucien <lucien@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/08/06 08:52:01 by lucien            #+#    #+#              #
#    Updated: 2021/08/31 10:14:51 by lucien           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= ft_ssl

FLASG = -Wall -Wextra -Werror

SRC	= 		./sources/first_steps.c \
			./sources/ft_md5/const.c

HEADER	= -I ./include/ft_ssl.h \
			./include/ft_md5.h

$(NAME):
	@make -C ./libft re
	@gcc -g $(FLAGS) -c $(SRC)
	@gcc -g $(FLAGS) -L ./libft -lft $(OBJ) -o $(NAME)

all: $(NAME)

clean:
	@rm -rf $(NAME)*

fclean: clean

re: fclean $(NAME)