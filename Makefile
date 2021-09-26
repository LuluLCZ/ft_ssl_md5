# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lucien <lucien@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/08/06 08:52:01 by lucien            #+#    #+#              #
#    Updated: 2021/09/26 15:33:56 by lucien           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ft_ssl
NAME1 = ft_ssl

CC = gcc

OPTIONS = -c

CFLAGS = -Wall -Wextra -Werror

RM = rm -Rfv

SRC =   const_md5.c \
		md5.c \
		utils_1.c \
		itoa_base.c \
		swap.c\
		sha256.c\
		const_sha256.c\
		read_file.c\
		parse_command.c\
		ft_ssl.c\
		sha_ops.c\
		md5_ops.c

SRC1 = $(SRC)

OBJ1 = $(SRC1:.c=.o)

DIR_SRC = sources
DIR_OBJ = objs

SRCS1 = $(addprefix $(DIR_SRC)/,$(SRC1))

OBJS1 = $(addprefix $(DIR_OBJ)/,$(OBJ1))

HEAD_DIR = ./libft/

all:  $(NAME)

$(NAME): $(NAME1)


$(NAME1) : libft $(OBJS1)
				$(RM) $(NAME1)
				$(CC) $(CFLAGS) -o $@ $(OBJS1) $(HEAD_DIR)/libft.a

$(DIR_OBJ)/%.o: $(DIR_SRC)/%.c
				@mkdir -p $(DIR_OBJ)
				$(CC) $(CFLAGS) -c -o $@ -I./includes/md5.h -I./includes/sha256.h -I./includes/.ft_ssl.h -I./malloc/includes/malloc.h -I./includes/.init.h -I./libft/includes $^

libft:
				make -C $(HEAD_DIR)

clean:
				$(RM) $(OBJS1) 
				cd $(HEAD_DIR) && $(MAKE) $@

fclean: clean
				$(RM) $(NAME1) 


				make -C $(HEAD_DIR) fclean

re: fclean all

.PHONY : all clean fclean re libft