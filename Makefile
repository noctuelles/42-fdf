# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: plouvel <plouvel@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/12/25 19:17:39 by plouvel           #+#    #+#              #
#    Updated: 2021/12/25 20:34:14 by plouvel          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CFLAGS		=	-Wall -Werror -Wextra \
				-I includes -I $(LIBFT_DIR)/includes -I $(MLIBX_DIR)

CLIBS		=	-L . -lft -lmlx

CC			=	cc

NAME		=	fdf

RM			=	rm -rf

LIBS_DIR	=	libs

LIBFT_DIR	=	$(LIBS_DIR)/libft

MLIBX_DIR	=	$(LIBS_DIR)/minilibx-linux

$(NAME):			makelibs

all:				$(NAME)

clean:

fclean:
					$(RM) libft.a libmlx.a

re:					fclean all

makelibs:
					@if [ ! -f libft.a ]; then \
						echo "No libft found..."; \
						echo "-> Making libft... <-"; \
						make -s -C $(LIBFT_DIR) all > /dev/null; \
						cp $(LIBFT_DIR)/libft.a . > /dev/null; \
						make -C $(LIBFT_DIR) fclean > /dev/null; \
						echo "Done."; \
					fi
					@if [ ! -f libmlx.a ]; then \
						echo "No MiniLibX found..."; \
						echo "-> Making MiniLibX... <-"; \
						make -s -C $(MLIBX_DIR) > /dev/null; \
						cp $(MLIBX_DIR)/libmlx_Linux.a libmlx.a > /dev/null; \
						make -C $(MLIBX_DIR) clean > /dev/null; \
						echo "Done."; \
					fi


