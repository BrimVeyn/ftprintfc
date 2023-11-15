# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bvan-pae <bryan.vanpaemel@gmail.com>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/10 13:53:02 by bvan-pae          #+#    #+#              #
#    Updated: 2023/11/15 13:12:11 by bvan-pae         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -Wall -Werror -Wextra
NAME = libftprintf.a
SRC = $(wildcard *.c)
AR = ar rcs
RAN = ranlib
LIBFTPATH = libft/
LIBFT = $(LIBFTPATH)/libft.a
OBJ = $(SRC:.c=.o)

DEF_COLOR = \033[0;39m
GRAY = \033[0;90m
RED = \033[0;91m
GREEN = \033[0;92m
YELLOW = \033[0;93m
BLUE = \033[0;94m
MAGENTA = \033[0;95m
CYAN = \033[0;96m
WHITE = \033[0;97m


all: $(NAME)

$(NAME): $(LIBFT) $(OBJ)
	cp $(LIBFT) .
	mv $(LIBFT) $(NAME)
	@echo "$(GREEN)Making library : $(NAME)"
	@printf "$(MAGENTA)"
	$(AR) $(NAME) $(OBJ)
	$(RAN) $(NAME)
	@printf "$(DEF_COLOR)"

$(LIBFT):
	make -C $(LIBFTPATH)

%.o: %.c
	@echo "$(YELLOW)Compiling : $< $(DEF_COLOR)"
	@printf "$(BLUE)"
	$(CC) $(CFLAGS) -c $< -o $@
	@printf "$(DEF_COLOR)"

clean:
	@printf "$(RED)"
	rm -f $(OBJ) $(BOBJ)
	make -C $(LIBFTPATH) clean
	@printf "$(DEF_COLOR)"

fclean: clean
	@printf "$(RED)"
	rm -f $(NAME)
	make -C $(LIBFTPATH) fclean
	@printf "$(DEF_COLOR)"

bonus:	all


re: fclean all

.PHONY: all clean fclean re bonus
