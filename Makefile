.PHONY          :   clean fclean re all clang debug
.DEFAULT_GOAL	:=	all

NAME            =   ft_ls

#           GCC
CC              =   cc
CFLAGS          =   -Wall -Wextra -Werror -MMD -MP
CPPFLAGS        =   -Iinclude/
LDFLAGS         =
LDLIBS          =

#			DEBUG
ifeq ($(DEBUG), 1)
	CFLAGS		+=	-g3 -fsanitize=address
endif

#           COMMON
BUILD_DIR       =   .build/
SRC_DIR         =   src/

#           SRC
SRC_FILES       =   main			\
					array			\
					block			\
					dir				\
					elem			\
					list			\
					ls				\
					msg				\
					print			\

OBJ             =   $(addprefix $(BUILD_DIR), $(addsuffix .o, $(SRC_FILES)))
DEPS            =   $(addprefix $(BUILD_DIR), $(addsuffix .d, $(SRC_FILES)))

#           RULES

all             :   $(NAME)

$(NAME)         :   $(OBJ)
				$(CC) $(CFLAGS) $(LDFLAGS) $(OBJ) $(LDLIBS) -o $(NAME)

$(BUILD_DIR)%.o :   $(SRC_DIR)%.c
				@mkdir -p $(@D)
				$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@

-include $(DEPS)

clean           :
				rm -rf $(BUILD_DIR)

fclean          :   clean
				rm -f $(NAME)

re              :   fclean all

debug           :
				$(MAKE) DEBUG=1 re

clang			:
				bear -- make -B