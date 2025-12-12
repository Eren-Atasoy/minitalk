# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: student <student@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/12/12 00:00:00 by student           #+#    #+#              #
#    Updated: 2025/12/12 00:00:00 by student          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME_SERVER	= server
NAME_CLIENT	= client

CC			= cc
CFLAGS		= -Wall -Wextra -Werror

SRC_DIR		= src
INC_DIR		= include

SRC_UTILS	= $(SRC_DIR)/utils.c
SRC_CUTILS	= $(SRC_DIR)/client_utils.c
SRC_SERVER	= $(SRC_DIR)/server.c $(SRC_UTILS)
SRC_CLIENT	= $(SRC_DIR)/client.c $(SRC_UTILS) $(SRC_CUTILS)

OBJ_SERVER	= $(SRC_SERVER:.c=.o)
OBJ_CLIENT	= $(SRC_CLIENT:.c=.o)

all: $(NAME_SERVER) $(NAME_CLIENT)

$(NAME_SERVER): $(OBJ_SERVER)
	$(CC) $(CFLAGS) $(OBJ_SERVER) -o $(NAME_SERVER)

$(NAME_CLIENT): $(OBJ_CLIENT)
	$(CC) $(CFLAGS) $(OBJ_CLIENT) -o $(NAME_CLIENT)

%.o: %.c $(INC_DIR)/minitalk.h
	$(CC) $(CFLAGS) -I$(INC_DIR) -c $< -o $@

clean:
	rm -f $(SRC_DIR)/*.o

fclean: clean
	rm -f $(NAME_SERVER) $(NAME_CLIENT)

re: fclean all

# Bonus
SRC_SERVER_BONUS	= $(SRC_DIR)/server_bonus.c $(SRC_UTILS)
SRC_CLIENT_BONUS	= $(SRC_DIR)/client_bonus.c $(SRC_UTILS) $(SRC_CUTILS)

OBJ_SERVER_BONUS	= $(SRC_SERVER_BONUS:.c=.o)
OBJ_CLIENT_BONUS	= $(SRC_CLIENT_BONUS:.c=.o)

bonus: fclean $(NAME_SERVER)_bonus $(NAME_CLIENT)_bonus

$(NAME_SERVER)_bonus: $(OBJ_SERVER_BONUS)
	$(CC) $(CFLAGS) $(OBJ_SERVER_BONUS) -o $(NAME_SERVER)

$(NAME_CLIENT)_bonus: $(OBJ_CLIENT_BONUS)
	$(CC) $(CFLAGS) $(OBJ_CLIENT_BONUS) -o $(NAME_CLIENT)

.PHONY: all clean fclean re bonus
