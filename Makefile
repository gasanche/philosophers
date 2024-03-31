# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gabsanch <gabsanch@student.42barcel>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/04 15:11:49 by gabsanch          #+#    #+#              #
#    Updated: 2024/03/31 17:58:24 by gabsanch         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo
CC = gcc
RM = rm -rf
FLAGS = -Wall -Wextra -Werror -g #-fsanitize=address -fsanitize=thread
SRC = main.c check_argv.c birth.c
INC = -I philo.h
OBJ = $(SRC:.c=.o)
DEP = $(SRC:.c=.d)

all: $(NAME)
%.o: %.c Makefile
	$(CC) -MMD $(FLAGS) -c $< -o $@ $(INC)
$(NAME): $(OBJ)
	$(CC) $(FLAGS) $(OBJ) -o $(NAME)
fclean: clean
	$(RM) $(NAME)
clean:
	$(RM) $(OBJ) $(DEP)
re: fclean all
.PHONY: all clean fclean re
-include $(DEP)
