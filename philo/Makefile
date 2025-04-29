#________________________MACROS

NAME				= philo

#____________DEBUGGING
RESET				= \033[0m
UNDERLINE			= \033[4m
BOLD				= \033[1m
RED					= \033[0;91m
GREEN				= \033[0;92m
YELLOW				= \033[0;93m
BLUE				= \033[0;94m
PURPLE				= \033[0;35m
CYAN				= \033[0;96m
WHITE				= \033[0;37m


#____________DIRECTORIES
SRC_DIR				= src/
HEAD_DIR			= inc/
OBJ_DIR				= $(SRC_DIR).build/

#____________FILES
ALL_SRC				= main.c \
					parsing.c \
					activities.c \
					init.c \
					loop.c \
					monitor.c \
					time.c \
					utils.c \


PREFIX_SRC			= $(addprefix $(SRC_DIR), $(ALL_SRC))

OBJ					= $(patsubst $(SRC_DIR)%.c, $(OBJ_DIR)%.o, $(PREFIX_SRC))
DEP					= $(OBJ:.o=.d)

DIRS				= $(sort $(dir $(OBJ)))

#____________UTILITIES
CC					= cc
CFLAGS				= -Wextra -Wall -Werror -MMD -MP

#________________________RULES

all : $(NAME)
	$(LOG__ALLSUCCESS)

-include $(DEP)

$(NAME): $(DIRS) $(OBJ)
	$(call logs, $(CYAN),"Compiling\ Executable")
	$(CC) $(CFLAGS) $(OBJ) -I$(HEAD_DIR) -o $(NAME)
	$(LOG__SUCCESS)

# Compile .o files, maintaining folder structure
$(OBJ_DIR)%.o : $(SRC_DIR)%.c
	$(call logs, $(CYAN),"Compiling\ OBJ\ files")
	$(CC) $(CFLAGS) -I$(HEAD_DIR) -c $< -o $@
	$(LOG__SUCCESS)

$(DIRS) :
	$(call logs, $(CYAN),"Creating\ directories")
	@mkdir -p $@
	$(LOG__SUCCESS)

clean : 
	$(call logs, $(YELLOW),"Cleaning\ OBJ\ files")
	rm -rf $(OBJ_DIR)
	$(LOG__SUCCESS)

fclean : clean
	$(call logs, $(YELLOW),"Cleaning\ Executable")
	rm -f $(NAME)
	$(LOG__SUCCESS)


debug: CFLAGS += -D DEBUG=1 -g -fsanitize=thread
debug: re
		$(call logs, $(GREEN),"Debug mode enabled")


re : fclean all


.PHONY : all clean fclean re