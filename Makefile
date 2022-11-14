NAME = philo
SRC = main.c \
	  init.c \
	  print.c \
	  smart_sleep.c \
	  utils.c
OBJS = main.o \
	   init.o \
	   print.o \
	   smart_sleep.o \
	   utils.o
CC = gcc
HEADER = includes/pipex.h
FLAGS = -Wall -Wextra -Werror
%.o: %.c
	@$(CC) $(FLAGS) -c $< -o $@
all: $(NAME)
$(NAME): $(OBJS)
	@$(CC) $(FLAGS) $^ -o $@
#	@mkdir objs
#	@mv $(OBJS) ./objs
clean:
		@/bin/rm -f $(OBJS)
		@/bin/rm -Rf obj
fclean: clean
		@/bin/rm -rf $(NAME)
		@/bin/rm -rf objs
		@/bin/rm -rf *.dSYM
re: fclean all
.PHONY: all clean fclean re