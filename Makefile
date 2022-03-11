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
SRCS		=	$(S)main.c \
				$(S)pipes.c $(S)execute.c \
				$(S)slaves.c \
				$(S)ft_split.c $(S)utils.c

# SRCS_BONUS	=	$(S_BONUS)0_main_bonus.c \
# 				$(S_BONUS)1_map_parse_bonus.c \
# 				$(S_BONUS)2_map_fill_bonus.c $(S_BONUS)3_map_check_bonus.c\
# 				$(S_BONUS)4_init_txtr_bonus.c

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
			make -C ./libft clean

fclean:		clean
			rm -rf $(NAME) $(NAME_BONUS)

re:			fclean all

.PHONY:		all bonus clean fclean re