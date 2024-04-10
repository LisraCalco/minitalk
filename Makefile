# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tlegendr <tlegendr@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/08 16:14:59 by tlegendr          #+#    #+#              #
#    Updated: 2024/04/10 14:45:49 by tlegendr         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Define the output names
SERVER_NAME := server
CLIENT_NAME := client

SERVER_NAME_BONUS := server_bonus
CLIENT_NAME_BONUS := client_bonus

# Source files for server and client
SERVER_SRC := server.c
CLIENT_SRC := client.c

SERVER_SRC_BONUS := server_bonus.c
CLIENT_SRC_BONUS := client_bonus.c

UTILS_SRC := minitalk.c ft_printf.c

# Object files derived from source files
SERVER_OBJ := $(SERVER_SRC:.c=.o)
CLIENT_OBJ := $(CLIENT_SRC:.c=.o)

SERVER_OBJ_BONUS := $(SERVER_SRC_BONUS:.c=.o)
CLIENT_OBJ_BONUS := $(CLIENT_SRC_BONUS:.c=.o)

UTILS_OBJ := $(UTILS_SRC:.c=.o)

# Compiler and compiler flags
CC := cc
CFLAGS := -g -Wall -Wextra -Werror -I/usr/include
LDFLAGS := -lm -lz

# Default target (builds both server and client)
all: $(SERVER_NAME) $(CLIENT_NAME) 

bonus: $(SERVER_NAME_BONUS) $(CLIENT_NAME_BONUS) 

# Pattern rule for compiling source files to object files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Build the server
$(SERVER_NAME): $(SERVER_OBJ) $(UTILS_OBJ)
	$(CC) -o $(SERVER_NAME) $(SERVER_OBJ) $(UTILS_OBJ) $(LDFLAGS)

# Build the client
$(CLIENT_NAME): $(CLIENT_OBJ) $(UTILS_OBJ)
	$(CC) -o $(CLIENT_NAME) $(CLIENT_OBJ) $(UTILS_OBJ) $(LDFLAGS)

# Build the server bonus
$(SERVER_NAME_BONUS): $(SERVER_OBJ_BONUS) $(UTILS_OBJ)
	$(CC) -o $(SERVER_NAME_BONUS) $(SERVER_OBJ_BONUS) $(UTILS_OBJ) $(LDFLAGS)

# Build the client bonus 
$(CLIENT_NAME_BONUS): $(CLIENT_OBJ_BONUS) $(UTILS_OBJ)
	$(CC) -o $(CLIENT_NAME_BONUS) $(CLIENT_OBJ_BONUS) $(UTILS_OBJ) $(LDFLAGS)

# Clean up object files
clean:
	rm -f $(SERVER_OBJ) $(CLIENT_OBJ) $(UTILS_OBJ) $(SERVER_OBJ_BONUS) $(CLIENT_OBJ_BONUS)

# Clean everything, including the final output
fclean: clean
	rm -f $(SERVER_NAME) $(CLIENT_NAME) $(SERVER_NAME_BONUS) $(CLIENT_NAME_BONUS)

# Rebuild the project
re: fclean all

# Phony target to avoid conflicts with files named "clean" or "fclean"
.PHONY: all clean fclean re
