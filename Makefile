# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: plouvel <plouvel@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/12/25 19:17:39 by plouvel           #+#    #+#              #
#    Updated: 2022/01/23 15:49:44 by plouvel          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


OBJS_DIR	=	objs

SRCS_DIR	=	srcs

SRCS		=	core/file_utils.c		\
				core/main_utils.c		\
				core/mlx.c				\
				core/parsing.c			\
				core/vertices.c			\
				core/vertices_utils.c	\
				drawing/line.c			\
				drawing/primitives.c	\
				gui/hud.c				\
				gui/keys.c				\
				renderer/render.c		\
				renderer/render_utils.c	\
				main.c

OBJS		=	$(addprefix $(OBJS_DIR)/, $(SRCS:.c=.o))

CFLAGS		=	-Wall -Werror -Wextra \
				-I includes -I $(LIBFT_DIR)/includes -I $(MLIBX_DIR) \
				-Ofast \
				-L . -lft -lmlx -lXext -lX11 -lm -lz

CC			=	cc

NAME		=	fdf

RM			=	rm -rf

LIBS_DIR	=	libs

LIBFT_DIR	=	$(LIBS_DIR)/libft

MLIBX_DIR	=	$(LIBS_DIR)/minilibx-linux

$(NAME):		libft.a libmlx.a $(OBJS)
				$(CC) $(OBJS) $(CFLAGS) -o $(NAME)

$(OBJS_DIR)/%.o:	$(SRCS_DIR)/%.c
				@mkdir -p $(dir $@)
				$(CC) $(CFLAGS) -c $< -o $@

all:			$(NAME)

clean:
				$(RM) $(OBJS_DIR)

fclean:			clean
				$(RM) libft.a libmlx.a
				$(RM) $(NAME)

re:				fclean all

libft.a:
				make -C $(LIBFT_DIR) all
				cp $(LIBFT_DIR)/libft.a .
				make -C $(LIBFT_DIR) fclean

libmlx.a:
				make -C $(MLIBX_DIR)
				cp $(MLIBX_DIR)/libmlx_Linux.a libmlx.a
				make -C $(MLIBX_DIR) clean

.PHONY:			all clean fclean re
