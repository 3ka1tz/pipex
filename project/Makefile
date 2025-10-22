# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: elopez-u <elopez-u@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/19 14:34:45 by elopez-u          #+#    #+#              #
#    Updated: 2025/01/13 10:51:44 by elopez-u         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex
CC = cc
CFLAGS = -Wall -Werror -Wextra

SRC = libft/ft_strlen.c \
	  libft/ft_strncmp.c \
	  libft/ft_strndup.c \
	  libft/ft_strjoin.c \
	  libft/ft_free.c \
	  libft/ft_split.c \
	  mandatory/pipex_utils.c \
	  mandatory/command_locator.c \
	  mandatory/command_executor.c \
	  mandatory/pipex.c

OBJ = $(SRC:.c=.o)

BONUS_SRC = libft/ft_strlen.c \
			libft/ft_strchr.c \
			libft/ft_strcmp.c \
			libft/ft_strncmp.c \
			libft/ft_strdup.c \
			libft/ft_strndup.c \
			libft/ft_strlcpy.c \
			libft/ft_strjoin.c \
			libft/ft_free.c \
			libft/ft_split.c \
	  		bonus/command_locator_bonus.c \
	  		bonus/command_executor_bonus.c \
			bonus/pipex_utils_bonus.c \
			bonus/get_next_line_bonus/get_next_line_bonus.c \
			bonus/here_doc.c \
			bonus/pipex_bonus.c
			
BONUS_OBJ = $(BONUS_SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ)

bonus: $(BONUS_OBJ)
	$(CC) $(CFLAGS) -o $(NAME) $(BONUS_OBJ)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(BONUS_OBJ)

fclean: clean
	rm -f $(NAME) $(NAME)_bonus $(OBJ) $(BONUS_OBJ)

re: fclean all

.PHONY: all bonus clean fclean re $(NAME)