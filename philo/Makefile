CC=cc
NAME=a.out
FLAGS= -Wall -Wextra -Werror -g
INC=
OBJ_DIR=obj/
SRCS=	helpers.c main.c initializers.c check_arguments.c util.c actions/eat.c \
		actions/sleep.c actions/take_forks.c actions/release_forks.c actions/think.c \
		set_last_mealtime.c thread_routine.c
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
