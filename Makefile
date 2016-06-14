#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: msoudan <msoudan@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2013/12/17 18:21:40 by msoudan           #+#    #+#              #
#    Updated: 2016/06/13 20:48:08 by msoudan          ###   ########.fr        #
#                                                                              #
#******************************************************************************#

CPATH = srcs
HPATH = includes
LIBPATH = libft

NAME = lem-in 
LIB = $(LIBPATH)/libft.a

CC = /usr/bin/gcc
RM = /bin/rm
CFLAGS = -Wall -Wextra -Werror -g

SRC += main.c
SRC += parse_lem.c
SRC += get_a_room.c
SRC += explore_new_domain.c
SRC += draw_room.c
SRC += wrong_turn.c
SRC += send_scouts.c
SRC += send_army.c
SRC += write_room.c
SRC += get_a_tube.c
SRC += get_x_y.c
SRC += bob_at_work.c
SRC += test_compatibility.c
SRC += delete_ways.c
SRC += delete_current_test.c

CFILES = $(patsubst %,$(CPATH)/%,$(SRC))
OFILES = $(patsubst %.c,%.o,$(CFILES))

.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(OFILES)
	@make -C $(LIBPATH)
	@$(CC) -L $(LIBPATH) -lft $^ -o $@
	@clear
	@echo "\033[36m\\o/ Finished ! \\o/\033[0m"

%.o: %.c
	@$(CC) -I $(HPATH) -I $(LIBPATH)/$(HPATH) $(CFLAGS) -c $^ -o $@

clean:
	@make -C $(LIBPATH) clean
	@$(RM) -f $(OFILES)

fclean: clean
	@make -C $(LIBPATH) fclean
	@$(RM) -f $(NAME)

re: fclean all
