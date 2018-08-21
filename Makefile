# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rtulchiy <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/02/13 18:49:17 by rtulchiy          #+#    #+#              #
#    Updated: 2018/05/15 18:55:21 by rtulchiy         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAMEVM = corewar
NAMEASM = asm
VMDIR = VM
ASMDIR = ASM_DIR

all:
	make -C $(VMDIR)
	make -C $(ASMDIR)
	mv $(VMDIR)/$(NAMEVM) .
	mv $(ASMDIR)/$(NAMEASM) .

clean:
	make clean -C $(VMDIR)
	make clean -C $(ASMDIR)

fclean: clean
	make fclean -C $(VMDIR)
	make fclean -C $(ASMDIR)
	rm -f $(NAMEVM)
	rm -f $(NAMEASM)

re: fclean all
