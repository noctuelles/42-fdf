# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: plouvel <plouvel@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/12/03 10:13:17 by plouvel           #+#    #+#              #
#    Updated: 2021/12/25 20:18:29 by plouvel          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

OBJS_DIR	=	objs/

SRCS_DIR	=	srcs/

SRCS		=	ft_memset.c 		\
				ft_bzero.c 			\
				ft_memcpy.c 		\
				ft_memmove.c 		\
				ft_memchr.c 		\
				ft_memcmp.c			\
				ft_calloc.c			\
				ft_strlen.c			\
				ft_strlcpy.c		\
				ft_strlcat.c		\
				ft_strncat.c		\
				ft_strncmp.c		\
				ft_strchr.c			\
				ft_strrchr.c		\
				ft_strnstr.c		\
				ft_strdup.c			\
				ft_strndup.c		\
				ft_straddc.c		\
				ft_straddbc.c		\
				ft_straddec.c		\
				ft_straddbs.c		\
				ft_straddes.c	 	\
				ft_strnew_nchar.c	\
				ft_strnew_chars.c	\
				ft_strmapi.c		\
				ft_striteri.c		\
				ft_split.c			\
				ft_substr.c			\
				ft_strjoin.c		\
				ft_strjoinc.c		\
				ft_strtrim.c		\
				ft_atoi.c			\
				ft_itoa.c			\
				ft_itoa_base.c		\
				ft_itoa_ubase.c		\
				ft_putchar_fd.c		\
				ft_putchar.c		\
				ft_putstr_fd.c		\
				ft_putstr.c			\
				ft_putendl_fd.c		\
				ft_putnbr_fd.c		\
				ft_putnbr_base_fd.c	\
				ft_putbin_fd.c		\
				ft_isalpha.c		\
				ft_isdigit.c		\
				ft_isalnum.c		\
				ft_isascii.c		\
				ft_isprint.c		\
				ft_toupper.c		\
				ft_tolower.c		\
				ft_lstnew.c			\
				ft_lstadd_front.c	\
				ft_lstsize.c		\
				ft_lstlast.c		\
				ft_lstadd_back.c	\
				ft_lstdelone.c		\
				ft_lstclear.c		\
				ft_lstiter.c		\
				ft_lstmap.c			\
				ft_printf/ft_printf.c			\
				ft_printf/printf_ansi.c			\
				ft_printf/printf_apply.c		\
				ft_printf/printf_compute.c		\
				ft_printf/printf_conversion.c	\
				ft_printf/printf_parsing.c		\
				ft_printf/printf_puts.c			\
				ft_printf/printf_utils.c		\
				gnl/get_next_line.c			\
				gnl/get_next_line_utils.c	\

OBJS		=	$(addprefix $(OBJS_DIR), $(SRCS:.c=.o))

CFLAGS		=	-Wall -Werror -Wextra -I includes

CC			=	cc

NAME		=	libft.a

RM			=	rm -rf

$(NAME): 		$(OBJS)
				@ar r ${NAME} ${OBJS}
				ranlib ${NAME}

$(OBJS_DIR)%.o:	$(SRCS_DIR)%.c
				@mkdir -p $(OBJS_DIR)
				@mkdir -p $(OBJS_DIR)ft_printf
				@mkdir -p $(OBJS_DIR)gnl
				${CC} ${CFLAGS} -c $< -o $@

all:			$(NAME)

clean:
				${RM} ${OBJS_DIR}

fclean:			clean
				${RM} ${NAME}

re:				fclean all

.PHONY:	all clean fclean re
