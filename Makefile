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
NAME_BONUS	=	pipex_bonus
CC			=	gcc
CFLAGS		=	-Wall -Wextra -Werror -fsanitize=address -g3
OBJS		=	$(SRCS:.c=.o)
OBJS_BONUS	=	$(SRCS_BONUS:.c=.o)
HDR			=	./inc/pipex.h
HDR_BONUS	=	./bonus/inc_bonus/pipex_bonus.h
S			=	./srcs/
S_BONUS		=	./bonus/srcs_bonus/
SRCS		=	$(S)0_main.c \
				$(S)1_redirect.c \
				$(S)2_a_execute.c \
				$(S)2_b_execute_env.c \
				$(S)utils_split.c \
				$(S)utils_free_crash.c \
				$(S)utils_libft.c $(S)utils_libft_mallocs.c

SRCS_BONUS	=	$(S_BONUS)0_main_bonus.c \
				$(S_BONUS)1_start.c \
				$(S_BONUS)2_heredoc.c \
				$(S_BONUS)3_redirect_bonus.c \
				$(S_BONUS)4_a_execute.c \
				$(S_BONUS)4_b_execute_env.c \
				$(S_BONUS)utils_pipes.c \
				$(S_BONUS)utils_gnl.c \
				$(S_BONUS)utils_split.c \
				$(S_BONUS)utils_free_crash.c \
				$(S_BONUS)utils_libft.c $(S_BONUS)utils_libft_mallocs.c

all:			$(NAME) $(NAME_BONUS)

$(NAME):		$(OBJS)
				$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

mandatory:		$(NAME)

bonus:			$(NAME_BONUS)

$(NAME_BONUS):	$(OBJS_BONUS)
				$(CC) $(CFLAGS) $(OBJS_BONUS) -o $(NAME_BONUS)

%.o:		%.c $(HDR) $(HDR_BONUS)
			$(CC) $(CFLAGS) -c -o $@ $< 

clean:
			rm -rf $(OBJS) $(OBJS_BONUS)

fclean:		clean
			rm -rf $(NAME) $(NAME_BONUS)

re:			fclean all

.PHONY:		all bonus clean fclean re