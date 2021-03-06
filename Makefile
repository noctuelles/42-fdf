# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: plouvel <plouvel@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/12/25 19:17:39 by plouvel           #+#    #+#              #
#    Updated: 2022/01/29 16:23:01 by plouvel          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


OBJS_DIR	=	objs

SRCS_DIR	=	srcs

INC_DIR		=	includes

SRCS		=	core/file_utils.c		\
				core/mlx.c				\
				core/parsing.c			\
				core/vertices.c			\
				core/vertices_utils.c	\
				core/key_handler.c		\
				drawing/line.c			\
				drawing/line_gradient.c	\
				drawing/primitives.c	\
				gui/hud.c				\
				gui/hud2.c				\
				gui/keys.c				\
				renderer/gradient.c		\
				renderer/render.c		\
				renderer/transform.c	\
				renderer/projection.c	\
				renderer/render_utils.c	\
				main.c					\
				main_utils.c

OBJS		=	$(addprefix $(OBJS_DIR)/, $(SRCS:.c=.o))

DEPS		=	$(addprefix $(OBJS_DIR)/, $(SRCS:.c=.d))

CFLAGS		=	-MMD -MP \
				-Wall -Werror -Wextra \
				-I includes -I $(LIBFT_DIR)/$(INC_DIR) -I $(MLIBX_DIR) \
				-O3


CLIBS		=	-L . -lft -lmlx -lXext -lX11 -lm -lz 

CC			=	cc

NAME		=	fdf

RM			=	rm -rf

LIBS_DIR	=	libs

LIBFT_DIR	=	$(LIBS_DIR)/libft

MLIBX_DIR	=	$(LIBS_DIR)/minilibx-linux

$(NAME):		libft.a libmlx.a $(OBJS)
				$(CC) $(OBJS) $(CFLAGS) $(CLIBS) -o $(NAME)

$(OBJS_DIR)/%.o:$(SRCS_DIR)/%.c
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

norm:
				norminette $(LIBFT_DIR) $(INC_DIR) $(SRCS_DIR)

bonus:			$(NAME)

-include $(DEPS)


.PHONY:			all clean fclean re bonus norm
