# **************************************************************************** #
#                                  Makefile                                    #
# **************************************************************************** #

NAME		= get_next_line_bonus.a

CC			= cc
CFLAGS		= -Wall -Wextra -Werror -D BUFFER_SIZE=$(BUFFER_SIZE)

# BUFFER_SIZE por defecto si no se pasa como argumento
BUFFER_SIZE ?= 42

# Archivos fuente de la parte bonus
SRCS_BONUS	= get_next_line_bonus.c get_next_line_utils_bonus.c
OBJS_BONUS	= $(SRCS_BONUS:.c=.o)

# Regla por defecto
all: $(NAME)

# Compila la versión obligatoria (solo formalidad)
$(NAME): bonus

# Regla para compilar la versión bonus
bonus: $(OBJS_BONUS)
	ar rcs $(NAME) $(OBJS_BONUS)

# Limpia archivos objeto
clean:
	rm -f $(OBJS_BONUS)

# Limpieza completa
fclean: clean
	rm -f $(NAME)

# Recompilación
re: fclean all

.PHONY: all clean fclean re bonus

