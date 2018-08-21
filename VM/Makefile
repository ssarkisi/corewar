# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rtulchiy <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/02/13 18:49:17 by rtulchiy          #+#    #+#              #
#    Updated: 2018/05/15 15:21:10 by rtulchiy         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = corewar

OBJSRC = main.c ft_error_usage.c ncurses_main.c generating_objects.c \
		 ncurses_printing.c read_cor.c update_mem.c modes.c \
		 service_update_mem.c service_process.c implement_general.c \
		 implement_st_sti.c implement_conds.c getters.c cmd_validation_1.c \
		 params_handle.c implement_load.c implement_load_index.c \
		 implement_add_sub.c cmd_validation_2.c ncurses_service.c \
		 service_general.c implement_addition.c

OBJC = $(OBJSRC:%.c=srcs/%.c)
OBJO = $(OBJSRC:.c=.o)
CFLAGS = -Wall -Werror -Wextra # -fsanitize=address
LIBDIR = libft

NCURSES = -lncurses

%.o: srcs/%.c
	gcc $(CFLAGS) -c $< -I includes

all: $(NAME)

$(NAME): $(OBJO)
	make -C $(LIBDIR)
	gcc $(CFLAGS) -o $(NAME) $(OBJO) -L./$(LIBDIR) -lft -I includes $(NCURSES)

clean:
	make clean -C $(LIBDIR)
	rm -f $(OBJO)

fclean: clean
	make fclean -C $(LIBDIR)
	rm -f $(NAME)

re: fclean all
