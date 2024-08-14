# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jfita <jfita@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/27 15:48:43 by jfita             #+#    #+#              #
#    Updated: 2024/05/03 15:55:11 by jfita            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME		=	pipex_m
BNAME		= 	pipex
CC			=	cc
CCFLAGS		=	-Wall -Wextra -Werror
LIBFT_DIR	=	libft
LIBFT		=	$(LIBFT_DIR)/libft.a

HDR_DIR		=	./includes/
HDR_FILE	=	pipex.h
HEADERS		=	$(addprefix $(HDR_DIR), $(HDR_FILE))

SRC_DIR		=	./srcs/
SRC_FILE	=	main.c \
				split.c \
				parsing.c \
				error.c \
				daycare.c \
				utils.c \
				frees.c

BSRC_DIR	=	./srcs_bonus/
BSRC_FILE	=	main_bonus.c \
				split_bonus.c \
				parsing_bonus.c \
				error_bonus.c \
				daycare_bonus.c \
				here_doc.c \
				utils_bonus.c \
				frees_bonus.c

SOURCES		=	$(addprefix $(SRC_DIR), $(SRC_FILE))
BSOURCES	=	$(addprefix $(BSRC_DIR), $(BSRC_FILE))

all: $(NAME) $(BNAME)

bonus: $(BNAME)

$(NAME): $(LIBFT) $(SOURCES)
	$(CC) $(CCFLAGS) -I$(HDR_DIR) -I$(LIBFT_DIR) -o $(NAME) $(SOURCES) $(LIBFT)

$(BNAME): $(LIBFT) $(BSOURCES)
	$(CC) $(CCFLAGS) -I$(HDR_DIR) -I$(LIBFT_DIR) -o $(BNAME) $(BSOURCES) $(LIBFT)

$(LIBFT):
	make -C $(LIBFT_DIR)

clean:
	rm -f $(NAME) $(BNAME)
	make -C $(LIBFT_DIR) clean

fclean: clean
	rm -f $(NAME) $(BNAME)
	make -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re