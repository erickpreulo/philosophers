# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: egomes <egomes@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/10/07 13:20:11 by egomes            #+#    #+#              #
#    Updated: 2021/11/12 15:45:20 by egomes           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC = philo.c srcs/utils.c srcs/validation.c srcs/philo_utils.c srcs/function.c

NAME = philo_one

INCLUD = -I .

CC = gcc -fsanitize=address -g

CFLAGS = -Wall -Wextra -Werror

AR = ar rcs

.c.o:
			@$(CC)  $(CFLAGS) $(INCLUD) -c $< -o $(<:.c=.o)

OBJ = $(SRC:.c=.o)

$(NAME):	$(OBJ)
			@$(CC) $(CFLAGS) $(OBJ) -o $(NAME)
			
all:		$(NAME)

test:	re
		@$(CC) $(CFLAGS) $(NAME) -fsanitize=address -g

clean:
		${shell find . -type f -name "*.o" -delete}

fclean: clean
	@rm -f $(NAME)

re: fclean all