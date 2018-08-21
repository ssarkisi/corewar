# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rtulchiy <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/02/13 18:49:17 by rtulchiy          #+#    #+#              #
#    Updated: 2018/04/20 21:44:03 by rtulchiy         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = asm

OBJSRC = b_arg.c b_free.c b_ft.c b_label.c b_param.c b_size.c  b_write.c b_write_functions.c b_val.c main.c \
		 v_list_f.c v_command.c v_command2.c v_in_brackets.c v_label_args.c v_label_list.c v_lib_overload.c \
		 v_list_init.c v_lst_fill.c get_next_line.c v_free.c v_name_comment.c v_opcode.c v_libreload2.c v_errors.c

OBJC = $(OBJSRC:%.c=srcs/%.c)
OBJO = $(OBJSRC:.c=.o)
CFLAGS = -Wall -Werror -Wextra
LIBDIR = libft


%.o: srcs/%.c
	gcc $(CFLAGS) -c $< -I includes

all: $(NAME)

$(NAME): $(OBJO)
	make -C $(LIBDIR)
	gcc $(CFLAGS) -o $(NAME) $(OBJO) -L./$(LIBDIR) -lft -I includes 
clean:
	make clean -C $(LIBDIR)
	rm -f $(OBJO)

fclean: clean
	make fclean -C $(LIBDIR)
	rm -f $(NAME)

re: fclean all