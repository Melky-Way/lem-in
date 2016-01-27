#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: msoudan <msoudan@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2013/11/21 12:34:07 by msoudan           #+#    #+#              #
#    Updated: 2014/03/22 15:46:05 by msoudan          ###   ########.fr        #
#                                                                              #
#******************************************************************************#

NAME = libft.a
CFLAGS += -Wall -Werror -Wextra -g
INCDIR = .
INCFILE = libft.h
SRCC += ft_atoi.c ft_bzero.c ft_isalnum.c ft_isalpha.c ft_isascii.c
SRCC += ft_isdigit.c ft_isprint.c ft_itoa.c ft_memalloc.c ft_memccpy.c
SRCC += ft_memchr.c ft_memcmp.c ft_memcpy.c ft_memdel.c ft_memmove.c
SRCC += ft_memset.c ft_putchar_fd.c ft_putchar.c ft_putendl_fd.c ft_putendl.c
SRCC += ft_putnbr_fd.c ft_putnbr.c ft_putstr_fd.c ft_putstr.c ft_strcat.c
SRCC += ft_strchr.c ft_strclr.c ft_strcmp.c ft_strcpy.c ft_strdel.c
SRCC += ft_strdup.c ft_strequ.c ft_striter.c ft_striteri.c ft_strjoin.c
SRCC += ft_strlcat.c ft_strlen.c ft_strmap.c ft_strmapi.c ft_strncat.c
SRCC += ft_strncmp.c ft_strncpy.c ft_strnequ.c ft_strnew.c ft_strnstr.c
SRCC += ft_strrchr.c ft_strsplit.c ft_strstr.c ft_strsub.c ft_strtrim.c
SRCC += ft_tolower.c ft_toupper.c ft_realloc.c ft_lstnew.c ft_dlist_del.c
SRCC += ft_dlist_head.c ft_dlist_insert.c ft_dlist_new.c ft_dlist_tail.c
SRCC += ft_dlist_valdel.c get_next_line.c ft_make_array.c ft_str_array.c
SRCC += ft_new_node.c ft_lstpushback.c ft_lstpushfront.c ft_lstclear.c
SRCC += ft_lstiter.c ft_create_new.c ft_isspace.c ft_lstprint.c
SRCC += ft_lst_softcopy.c ft_lst_popfront.c ft_lst_popback.c ft_lst_swaptail.c
SRCC += ft_arrjoin.c ft_dlist_iter.c ft_lst_swap.c ft_is_int.c ft_power.c
SRCC += ft_lstadd.c ft_lstdel.c ft_lstdelone.c ft_lstmap.c

OBJS = $(SRCC:.c=.o)

.PHONY: all
all: $(NAME)

%.o: %.c $(INCFILE)
	@gcc $(CFLAGS) -I $(INCDIR) -o $@ -c $<

$(NAME): $(OBJS)
	@ar -rcs $(NAME) $(OBJS)
	@ranlib $(NAME)

.PHONY: clean
clean:
	@rm -f $(OBJS)

.PHONY: fclean
fclean: clean
	@rm -f $(NAME)

.PHONY: re
re: fclean all
