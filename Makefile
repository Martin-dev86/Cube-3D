# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cagarci2 <cagarci2@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/22 12:45:34 by cagarci2          #+#    #+#              #
#    Updated: 2024/03/22 12:45:34 by cagarci2         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


DEL_LINE =		\033[2K
ITALIC =		\033[3m
BOLD =			\033[1m
DEF_COLOR =		\033[0;39m
GRAY =			\033[0;90m
RED =			\033[0;91m
GREEN =			\033[0;92m
YELLOW =		\033[0;93m
BLUE =			\033[0;94m
MAGENTA =		\033[0;95m
CYAN =			\033[0;96m
WHITE =			\033[0;97m
BLACK =			\033[0;99m
ORANGE =		\033[38;5;209m
BROWN =			\033[38;2;184;143;29m
DARK_GRAY =		\033[38;5;234m
MID_GRAY =		\033[38;5;245m
DARK_GREEN =	\033[38;2;75;179;82m
DARK_YELLOW =	\033[38;5;143m

NAME = Cube_3D

SRC_DIR = ./ ./Execute ./Parse
LIBMLX	= Library/MLX42
FT_PRINTF = Library/ft_printf
LIBFT	= Library/Libft

SRC_FILES =		$(shell find $(SRC_DIR) -name '*.c')
LIBS	= $(LIBMLX)/build/libmlx42.a $(LIBFT)/libft.a -ldl -lglfw -pthread -lm  -L"/Users/$(USER)/.brew/opt/glfw/lib/" -pthread -lm $(FT_PRINTF)/ft_printf.a -ldl -lglfw -L"/Users/$(USER)/.brew/opt/glfw/lib/" -pthread -lm
OBJ_SRC		=	Parse/check_errors.c Parse/input_parse.c

HEADER_DIR	=	includes
HEADER_SRCS	=	cube3D.h \
HEADER		=	$(addprefix $(HEADER_DIR)/, $(HEADER_SRCS))

CC = gcc

CFLAGS = -Wall -Werror -Wextra -g -I$(LIBMLX)/include/MLX42 -Iincludes -I$(LIBFT) -I$(FT_PRINTF)

RM = rm -f

all: 	libmlx libft ft_printf $(NAME) 

libmlx:
	@cmake $(LIBMLX) -B $(LIBMLX)/build > /dev/null 2>&1 && make --no-print-directory -C $(LIBMLX)/build -j4

libft:
	@make --no-print-directory -C $(LIBFT)

ft_printf:
	@make --no-print-directory -C $(FT_PRINTF)

%.o: %.c Makefile
	@echo "${YELLOW} • $(CYAN)COMPILE ${RED}→ $(DARK_GRAY)$< ${WHITE}✓$(DEF_COLOR)"
	@$(CC) $(CFLAGS) -L./$(FT_PRINTF) -c $< -o $@

$(NAME):	$(OBJ_SRC) 
			@$(CC) $(OBJ_SRC) $(LIBS) -o $(NAME) 
			@echo "\n${YELLOW} ► $(GREEN)$(BOLD)Created $(NAME) correctly$(DEF_COLOR)\n"

clean:
	@make clean -C $(LIBFT) > /dev/null 2>&1
	@make clean -C $(FT_PRINTF) > /dev/null 2>&1
	@$(RM) $(OBJ_SRC) 
	@find $(LIBMLX)/build -type f ! -name '*.a' -delete
	@find $(LIBMLX)/build -type d -empty -delete
	@echo "\n${YELLOW} ¤ $(ORANGE)objects cleaned successfully ${GREEN}✓$(DEF_COLOR)\n"

fclean: clean	
	@$(RM) $(NAME)
	@$(RM) $(LIBFT)/libft.a
	@$(RM) $(LIBMLX)/build/libmlx42.a
	@$(RM) $(FT_PRINTF)/Ftprintf.a
	@echo "${YELLOW} ¤ $(ORANGE)executables cleaned successfully ${GREEN}✓$(DEF_COLOR)\n"

re: fclean all 

.PHONY: all clean fclean re libmlx libft ft_printf