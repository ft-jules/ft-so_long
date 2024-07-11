# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jpointil <jpointil@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/28 16:08:02 by jpointil          #+#    #+#              #
#    Updated: 2024/07/09 18:33:43 by jpointil         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# ################################### BASICS ###################################

SO_LONG_NAME    =   so_long

CC              =   cc
FLAG            =   -Wall -Wextra -Werror -g3

LIBFT_PATH      =   libft/
LIBFT_FILE      =   libft.a
LIBFT_LIB       =   $(LIBFT_PATH)/$(LIBFT_FILE)

MLX_PATH        =   minilibx-linux/
MLX_FLAGS       =   -lX11 -lXext -fPIE
MLX_FILE        =   libmlx.a
MLX_LIB         =   $(MLX_PATH)/$(MLX_FILE)
MLX_EX          =   $(MLX_LIB) $(MLX_FLAGS)

# ################################### SOURCES ###################################

SO_LONG_SRC     =   src/so_long.c src/map_parsing.c src/map_is_playable.c src/error_free.c src/visuals.c src/movements.c


# #################################### MANDATORY ####################################

SO_LONG_OBJ     =   $(SO_LONG_SRC:.c=.o)
SO_LONG_DEPS    =   $(SO_LONG_SRC:.c=.d)

-include $(SO_LONG_DEPS)

.c.o:
	@printf "\r\033[K[so_long] \033[0;32mBuilding : $<\033[0m"
	@$(CC) $(FLAG) -MMD -c $< -o $@

# #################################### BONUS ####################################

# #################################### RULES ####################################

all:    $(SO_LONG_NAME)

# bonus:

$(LIBFT_LIB):
	@make -C $(LIBFT_PATH)

$(MLX_LIB):
	@printf "\r\033[K[mlx] \033[0;32mLinking...\033[0m"
	@make -sC $(MLX_PATH)

$(SO_LONG_NAME): $(LIBFT_LIB) $(MLX_LIB) $(SO_LONG_OBJ)
	@printf "\r\033[K[so_long] \033[0;32mLinking...\033[0m"
	@$(CC) $(SO_LONG_OBJ) $(LIBFT_LIB) $(MLX_EX) -o $(SO_LONG_NAME) -lm 
	@printf "\r\033[K[so_long] \033[0;32mDone!\033[0m\n"

clean:
	@make clean -sC $(LIBFT_PATH)
	@make clean -sC $(MLX_PATH)
	@rm -f $(SO_LONG_OBJ) $(SO_LONG_DEPS)
	@printf "[So_long] \033[1;31mCleaned .o and .d!\033[0m\n"

fclean: clean
	@rm -f $(SO_LONG_NAME)
	@make fclean -C $(LIBFT_PATH)
	@printf "[So_long] \033[1;31mCleaned all!\033[0m\n"

re: fclean all

.PHONY: all clean fclean re
