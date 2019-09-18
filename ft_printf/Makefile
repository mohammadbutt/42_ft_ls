# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mbutt <marvin@42.fr>                       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/08/07 15:20:38 by mbutt             #+#    #+#              #
#    Updated: 2019/09/13 15:37:54 by mbutt            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NC:=\033[0m
GREEN:=\033[1;32m
ORANGE:=\033[0;33m
YELLOW:=\033[1;33m
CYAN:=\033[1;36m

NAME = libftprintf.a
CC = gcc
CFLAGS = -Wall -Wextra -Werror -I. -c

#SRC = $(filter-out main.c, $(wildcard *.c)) // Changing path to srcs
#MINI_LIBFT = mini_libft/*.c				 // Changing path to srcs

#SRC = $(filter-out srcs/main.c, $(wildcard srcs/*.c)) // Not using wildcard
#MINI_LIBFT = srcs/mini_libft/*.c                      // Including files  manually

SRC = srcs/append_to_buffer.c  				\
	  srcs/collect_and_cancel_flags.c		\
	  srcs/collect_width_precision_length_type.c	\
	  srcs/ft_itoa_min_handler.c			\
	  srcs/ft_printf.c				\
	  srcs/parsing.c				\
	  srcs/type_field_b.c				\
	  srcs/type_field_c.c				\
	  srcs/type_field_d_i.c				\
	  srcs/type_field_f.c				\
	  srcs/type_field_o.c				\
	  srcs/type_field_p.c				\
	  srcs/type_field_percent.c			\
	  srcs/type_field_s.c				\
	  srcs/type_field_u.c				\
	  srcs/type_field_x.c				\
	  srcs/type_field_x_remaining_conditions.c	\

MINI_LIBFT = srcs/mini_libft/ft_atoi.c			\
			 srcs/mini_libft/ft_bzero.c	\
			 srcs/mini_libft/ft_ftoa.c	\
			 srcs/mini_libft/ft_hex.c	\
			 srcs/mini_libft/ft_isdigit.c	\
			 srcs/mini_libft/ft_itoa_base.c	\
			 srcs/mini_libft/ft_strcat.c	\
			 srcs/mini_libft/ft_strcpy.c	\
			 srcs/mini_libft/ft_strlen.c	\
			 srcs/mini_libft/utility.c	\

OBJ = *.o

all: $(NAME)

$(NAME):
	@echo "${CYAN}Compiling Makefile.${NC}"
	$(CC) $(CFLAGS) $(SRC) $(MINI_LIBFT)
	ar rc $(NAME) $(OBJ)
	@echo "${GREEN}Generated libftprintf.a static library succesfully.${NC}"

clean:
	rm -rf $(OBJ)
	@echo "${ORANGE}Removed object files.${NC}"

fclean:
	rm -rf $(NAME) $(OBJ)
	@echo "${ORANGE}Removed object files.${NC}"
	@echo "${YELLOW}Removed static library.${NC}"

re: fclean all
.PHONY: all clean fclean re
