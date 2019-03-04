# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: squiquem <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/12/23 19:01:27 by squiquem          #+#    #+#              #
#    Updated: 2018/01/04 22:19:01 by squiquem         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.PHONY			:	all clean fclean re

NAME			=	fdf

SRC_DIR			=	./sources/

OBJ_DIR			=	./objects/

CPPFLAGS 		=	-I includes/

SRC_FILES		=	main.c \
					hook.c \
					draw.c \
					help.c \
					parsing.c \
					cal_matrice.c \
					matrice.c \
					color.c \

OBJ_FILES		=	$(SRC_FILES:.c=.o)

SRC				=	$(addprefix $(SRC_DIR)/,$(SRC_FILES))

OBJ				=	$(addprefix $(OBJ_DIR), $(OBJ_FILES))

LDFLAGS			=	-L libft/

LFT				=	-lft

CC				=	gcc

CFLAGS			=	-Wall -Wextra -Werror

MLX				=	-lmlx -framework OpenGL -framework AppKit

all				:	$(NAME)

$(NAME)			:	$(OBJ)
	@make -C libft/
	@echo "\033[34mCreation of FdF ...\033[0m"
	@$(CC) $(CFLAGS) $(LDFLAGS) $(LFT) $(OBJ) -o $@ -L. $(MLX)
	@printf '\033[4m'
	@printf "\033[32m[ ✔ ] FdF Created\n\033[0m"

$(OBJ_DIR)%.o	:	$(SRC_DIR)%.c
	@mkdir $(OBJ_DIR) 2> /dev/null || true
	@$(CC) $(CFLAGS) $(CPPFLAGS) -o $@ -c $<
	@printf '\033[0m[ ✔ ] %s\n\033[0m' "$<"

clean			:
	@make fclean -C libft/
	@rm -f $(OBJ)
	@rmdir $(OBJ_DIR) 2> /dev/null || true
	@printf '\033[4m'
	@echo "\033[31mFdF:\033[0m"
	@printf '\033[31m[ ✔ ] %s\n\033[0m' "Clean Object Files"

fclean			:	clean
	@rm -f $(NAME)
	@printf '\033[31m[ ✔ ] %s\n\033[0m' "Clean Binary File"

re				:	fclean all
