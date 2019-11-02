# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mbutt <marvin@42.fr>                       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/09/18 15:35:11 by mbutt             #+#    #+#              #
#    Updated: 2019/11/01 22:00:19 by mbutt            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NC:=\033[0m
GREEN:=\033[1;32m
ORANGE:=\033[0;33m
YELLOW:=\033[1;33m
CYAN:=\033[1;36m

NAME = ft_ls
CC = gcc
#CFLAGS = -Wall -Wextra -Werror -I. -c
CFLAGS = -I. -c -g
WFLAGS = -Wall -Wextra -Werror
DEBUG = -fsanitize=address -ggdb

SRC = *.c
OBJ = *.o
#OBJ = $(SRC:.c=.o)

FT_PRINTF_DIR = ft_printf/
FT_PRINTF_STATIC = ft_printf/libftprintf.a

all: $(NAME)

$(NAME):
	@make -C $(FT_PRINTF_DIR) # runs Makefile for ft_printf
	@echo "${CYAN}Compiling Makefile for ft_ls...${NC}"
	@$(CC) $(CFLAGS) $(WFLAGS) $(SRC) # Creates .o(object) files
	@$(CC) $(OBJ) $(FT_PRINTF_STATIC) $(DEBUG) -o $(NAME)
	@echo "${GREEN}Generated ft_ls succesfully.${NC}"	

clean:
	make clean -C ft_printf/
	/bin/rm -rf $(OBJ)
	@echo "${ORANGE}Removed object files for ft_ls.${NC}"

fclean:
	make fclean -C ft_printf/
	/bin/rm -rf $(NAME) $(OBJ)
	@echo "${ORANGE}Removed obect files for ft_ls.${NC}"
	@echo "${YELLOW}Removed ft_ls.${NC}"

re: fclean all
.PHONY: all clean fclean re
