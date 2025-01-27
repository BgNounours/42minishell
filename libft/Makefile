# The interesting part
NAME = libft.a
SRCS = ./
INCLUDES = ./
FUNCTIONS = \
		isalpha isdigit isalnum isascii isprint \
		toupper tolower \
		strncmp strlen strlcpy strlcat strchr strrchr strnstr strdup \
		strmapi striteri substr strjoin strtrim split \
		memset bzero memcpy memmove memchr memcmp calloc \
		atoi itoa \
		putchar_fd putstr_fd putendl_fd putnbr_fd
CODE = $(addprefix ft_, $(FUNCTIONS))

# It works and I probably won't change it for the rest of my life
C_FILES = $(addsuffix .c,$(addprefix $(SRCS),$(CODE)))
O_FILES = $(addsuffix .o,$(addprefix $(SRCS),$(CODE)))
CC = cc -Wall -Wextra -Werror
AR = ar rcs
MAKE = make

all : $(NAME)

$(NAME) : $(O_FILES)
	$(AR) $(NAME) $(O_FILES)

%.o : %.c
	$(CC) -I $(INCLUDES) -c $< -o $@

clean :
	rm -f $(O_FILES)

fclean : clean
	rm -f $(NAME)

re : fclean all

.PHONY : all clean fclean re
