CC=cc
NAME=philosopher
FLAGS= -Wall -Wextra -Werror -g
INC=
OBJ_DIR=obj/
SRCS=	main.c util1.c util2.c check_arguments.c actions/eat.c thread_data.c \
		actions/sleep.c actions/take_forks.c actions/release_forks.c actions/think.c \
		thread_routine.c create_locks.c observe.c
OBJS=$(SRCS:.c=.o)
OBJS := $(addprefix $(OBJ_DIR), $(OBJS))

all: $(NAME)

$(NAME): $(OBJ_DIR) $(OBJS)
		$(CC) $(FLAGS) $(INC) $(OBJS) -o $(NAME)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(OBJ_DIR)%.o: %.c | $(OBJ_DIR)
	mkdir -p $(dir $@)
	$(CC) $(FLAGS) $(INC) -c $< -o $@

clean:
	$(RM) -r $(OBJ_DIR)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean re
