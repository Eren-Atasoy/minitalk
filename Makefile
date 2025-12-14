# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: eratasoy <eratasoy@student.42istanbul.c    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/12/14 16:37:14 by eratasoy          #+#    #+#              #
#    Updated: 2025/12/14 16:37:14 by eratasoy         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME		= minitalk
NAME_SERVER	= server
NAME_CLIENT	= client

CC			= cc
CFLAGS		= -Wall -Wextra -Werror

SRC_DIR		= src
INC_DIR		= include
LIBFT_DIR	= libft
LIBFT		= $(LIBFT_DIR)/libft.a

SRC_SERVER	= $(SRC_DIR)/server.c
SRC_CLIENT	= $(SRC_DIR)/client.c

OBJ_SERVER	= $(SRC_SERVER:.c=.o)
OBJ_CLIENT	= $(SRC_CLIENT:.c=.o)

all: $(NAME)

$(NAME): $(LIBFT) $(NAME_SERVER) $(NAME_CLIENT)

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

$(NAME_SERVER): $(OBJ_SERVER) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJ_SERVER) $(LIBFT) -o $(NAME_SERVER)

$(NAME_CLIENT): $(OBJ_CLIENT) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJ_CLIENT) $(LIBFT) -o $(NAME_CLIENT)

$(SRC_DIR)/%.o: $(SRC_DIR)/%.c $(INC_DIR)/minitalk.h $(LIBFT_DIR)/libft.h
	$(CC) $(CFLAGS) -I$(INC_DIR) -I$(LIBFT_DIR) -c $< -o $@

clean:
	$(MAKE) -C $(LIBFT_DIR) clean
	rm -f $(SRC_DIR)/*.o

fclean: clean
	$(MAKE) -C $(LIBFT_DIR) fclean
	rm -f $(NAME_SERVER) $(NAME_CLIENT)

re: fclean all


SRC_SERVER_B	= $(SRC_DIR)/server_bonus.c
SRC_CLIENT_B	= $(SRC_DIR)/client_bonus.c

OBJ_SERVER_B	= $(SRC_SERVER_B:.c=.o)
OBJ_CLIENT_B	= $(SRC_CLIENT_B:.c=.o)

bonus: fclean $(LIBFT) $(NAME_SERVER)_bonus $(NAME_CLIENT)_bonus

$(NAME_SERVER)_bonus: $(OBJ_SERVER_B) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJ_SERVER_B) $(LIBFT) -o $(NAME_SERVER)

$(NAME_CLIENT)_bonus: $(OBJ_CLIENT_B) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJ_CLIENT_B) $(LIBFT) -o $(NAME_CLIENT)

$(SRC_DIR)/%_bonus.o: $(SRC_DIR)/%_bonus.c $(INC_DIR)/minitalk_bonus.h $(LIBFT_DIR)/libft.h
	$(CC) $(CFLAGS) -I$(INC_DIR) -I$(LIBFT_DIR) -c $< -o $@

.PHONY: all clean fclean re bonus
