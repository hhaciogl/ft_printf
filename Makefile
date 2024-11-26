NAME = libftprintf.a
DEP_NAME = libft/libft.a
C_FILES = ft_printf.c _printf_one.c _printf_two.c
O_FILES = $(C_FILES:.c=.o)
CFLAGS = -Wall -Wextra -Werror
CC = cc

all: $(NAME)

$(NAME): $(DEP_NAME) $(O_FILES)
	ar src $(DEP_NAME) $(O_FILES) && mv $(DEP_NAME) $(NAME)


$(DEP_NAME):
	cd ./libft && $(MAKE)

clean:
	rm -f $(O_FILES)
	cd ./libft && $(MAKE) clean

fclean: clean
	rm -f $(NAME)
	cd ./libft && $(MAKE) fclean

re: fclean all
	cd ./libft && $(MAKE) re

norm:
	norminette $(C_FILES) ft_printf.h

.PHONY: clean all re fclean norm