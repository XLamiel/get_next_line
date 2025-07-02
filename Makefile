# Nombre de la libreria estatica
NAME = get_next_line.a

# Compilador y flags
CC = cc
CFLAGS = -Wall -Wextra -Werror
BUFFER_SIZE ?= 42  # Valor por defecto, pero se puede cambiar al llamar a 'make'

# Archivos fuente y objetos
SRCS = get_next_line.c get_next_line_utils.c
OBJS = $(SRCS:.c=.o)

# Regla principal: compila todos los objetos y crea la biblioteca
all: $(NAME)

$(NAME): $(OBJS)
	ar rcs $(NAME) $(OBJS)

# Regla para compilar cada .c en .o
%.o: %.c
	$(CC) $(CFLAGS) -D BUFFER_SIZE=$(BUFFER_SIZE) -c $< -o $@

# Limpia los objetos
clean:
	rm -f $(OBJS)

# Limpia objetos y el ejecutable/biblioteca
fclean: clean
	rm -f $(NAME)

# Recompila desde cero
re: fclean all

# Evita conflictos con nombres de archivos
.PHONY: all clean fclean re
