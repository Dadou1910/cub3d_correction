MAKEFLAGS += --no-print-directory
NAME = libft.a
SOURCES = ft_atoi.c ft_bzero.c ft_isalnum.c ft_isalpha.c\
 			ft_isascii.c ft_isdigit.c ft_isprint.c ft_strchr.c\
			ft_strdup.c ft_strlen.c ft_strncmp.c ft_strnstr.c\
			ft_strrchr.c ft_tolower.c ft_toupper.c ft_memcpy.c\
			ft_memmove.c ft_itoa.c ft_putchar_fd.c ft_putstr_fd.c\
			ft_putnbr_fd.c ft_split.c ft_strlcat.c ft_substr.c\
			ft_strjoin.c ft_striteri.c ft_calloc.c ft_memcmp.c\
			ft_memset.c ft_strlcpy.c ft_strmapi.c ft_strtrim.c\
			ft_putendl_fd.c ft_memchr.c ft_strcmp.c

OBJECTS = ${SOURCES:.c=.o}
CC = gcc
CFLAGS = -Wall -Wextra -Werror -g3
all: $(NAME)

.c.o :
	@$(CC) $(CFLAGS) -c $< -o ${<:.c=.o} -I ./

$(NAME): $(OBJECTS)
	@ar	-rc	$(NAME)	$(OBJECTS)

clean:
	@rm -rf $(OBJECTS)
fclean:
	@rm -rf	$(NAME)	$(OBJECTS)
re:
	@rm -rf all

.PHONY: all re fclean clean
