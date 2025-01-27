##### THE INTERESTING PART #####
NAME = minishell
# src directory
SRCS = src/
# include directory
INCLUDES = include/ libtf/ libft/
# .c files in src/ without the extension
CODE = main ask_command error path parse_command exec_command builtin builtin2 \
	signals cool_readline variables parse_command_utils export_print_builtin \
	parse_command_read_string parse_command_read_element variables_utils \
	export_builtin variables2
# directories to 'make'
LIBRARIES = libtf libft
# .a files to include
LIBRARIES_FILES = libtf/libtf.a libft/libft.a
# to use with the flags -L and -l
LIBRARIES_LINK =
# to use with the flag -l
LINK =
# flags to add to the compiler
MORE_FLAGSS = $(MORE_FLAGS) $(addprefix -L,$(LIBRARIES_LINK)) $(addprefix -l,$(LIBRARIES_LINK) $(LINK)) $(addprefix -I,$(INCLUDES))
##### END OF THE INTERESTING PART #####


C_FILES = $(addsuffix .c,$(addprefix $(SRCS),$(CODE)))
O_FILES = $(addsuffix .o,$(addprefix $(SRCS),$(CODE)))
ifdef DEBUG
CC = cc -Wall -Wextra -Werror -g
else
CC = cc -Wall -Wextra -Werror
endif



##### PUBLIC RULES #####
all : $(NAME)
	@echo "\t\t \e[0;92m\(^o^)/  \e[0;102;30;1m $(NAME) made! \e[0;92m \(^o^)/\e[0m"

clean :
	@echo "\e[30;47;1m  $(NAME): removing *.o files...  \e[0m"
	-rm -f $(O_FILES)
	@echo "\e[30;47;1m  $(NAME): removing *.o files finished!  \e[0m"

fclean : clean
	@echo "\e[30;47;1m  $(NAME): fclean...  \e[0m"
	$(foreach lib,$(LIBRARIES), make fclean -C $(lib) || make clean -C $(lib); )
	-rm -f $(NAME)
	@echo "\e[30;47;1m  $(NAME): fclean finished!  \e[0m"

re : clean all

debug :
	make all DEBUG=yes



$(NAME) : $(O_FILES) $(LIBRARIES)
	@echo "\e[30;47;1m  $(NAME): linking...  \e[0m"
	$(CC) -lreadline -o $(NAME) $(O_FILES) $(LIBRARIES_FILES) $(MORE_FLAGSS)
	@echo "\e[30;47;1m  $(NAME): linked!  \e[0m"

$(LIBRARIES) :
	@echo "\e[30;47;1m  $(NAME): making library $@...  \e[0m"
ifdef DEBUG
	make -C $@ debug || make -C $@
else
	make -C $@
endif
	@echo "\e[30;47;1m  $(NAME): library $@ made!  \e[0m"

%.o : %.c
	$(CC) -c $< -o $@ $(MORE_FLAGSS)

.PHONY : all debug clean fclean re $(LIBRARIES)
