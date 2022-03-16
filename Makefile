# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lrandria <lrandria@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/11 02:55:05 by lrandria          #+#    #+#              #
#    Updated: 2022/03/11 02:55:05 by lrandria         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	pipex
# NAME_BONUS	=	pipex_bonus
CC			=	gcc
CFLAGS		=	-Wall -Wextra -Werror -fsanitize=address -g3
OBJS		=	$(SRCS:.c=.o)
# OBJS_BONUS	=	$(SRCS_BONUS:.c=.o)
# HDR_BONUS	=	./bonus/inc/pipex_bonus.h
HDR			=	./inc/pipex.h
S			=	./srcs/
# S_BONUS		=	./bonus/srcs/
SRCS		=	$(S)0_main.c \
				$(S)1_redirect.c \
				$(S)2_find_all_paths.c \
				$(S)3_execute.c \
				$(S)utils_split.c $(S)utils_libft.c $(S)utils_libft_mallocs.c \
				$(S)utils_free_crash.c

# SRCS_BONUS	=	$(S)0_main.c \
					$(S)1_redirect.c \
					$(S)2_find_all_paths.c \
					$(S)3_execute.c \
					$(S)utils_split.c $(S)utils_libft.c $(S)utils_libft_mallocs.c \
					$(S)utils_free_crash.c

all:			$(NAME)

$(NAME):		$(OBJS)
				$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

mandatory:		$(NAME)

# bonus:			$(NAME_BONUS)

# $(NAME_BONUS):	$(OBJS_BONUS)
# 				$(CC) $(CFLAGS) $(OBJS_BONUS) -o $(NAME_BONUS)

%.o:		%.c $(HDR)
			$(CC) $(CFLAGS) -c -o $@ $< 

clean:
			rm -rf $(OBJS)

fclean:		clean
			rm -rf $(NAME)

re:			fclean all

.PHONY:		all bonus clean fclean re