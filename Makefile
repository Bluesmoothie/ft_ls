.PHONY			:	clean fclean re all norm FORCE

NAME			=   ft_ls

#			GCC

CC				=	cc
CFLAGS			=	-Wall -Wextra -Werror
CFLAGS			+=	-MMD -MP
CFLAGS			+=	$(INCLUDE)
CFLAGS			+=	-g3
LIBSFLAGS		=	-L$(LIBFT) -lft_ex

#			COMMON

BUILD_DIR		=	.build/
SRC_DIR			=	src/
INCLUDE 		=	-Iinclude/ -I$(LIBFT)/include/

#			SRC

SRC_FILES		=	main				\
					data				\
					data2				\
					debug				\
					error				\
					ft_getcwd			\
					ft_ls				\
					parse				\
					print				\
					time				\
					utils				\
					verifs				\
					t_lslst/t_lslst		\
					t_lslst/t_lslst2	\

SRC 			= 	$(addprefix $(SRC_DIR), $(addsuffix .c, $(SRC_FILES)))
OBJ 			= 	$(addprefix $(BUILD_DIR), $(addsuffix .o, $(SRC_FILES)))
DEPS 			= 	$(addprefix $(BUILD_DIR), $(addsuffix .d, $(SRC_FILES)))

#			LIBFT

LIBFT			=	libft
LIBFT_A			=	$(LIBFT)/libft_ex.a

#			RULES

all				:	$(NAME)

$(NAME)			:	$(BUILD_DIR) $(OBJ) $(LIBFT_A)
				$(CC) $(CFLAGS) $(OBJ) $(LIBSFLAGS) -o $(NAME)

$(BUILD_DIR)	:
				mkdir -p $(BUILD_DIR)
				mkdir -p $(BUILD_DIR)t_lslst

$(BUILD_DIR)%.o	: 	$(SRC_DIR)%.c
				$(CC) $(CFLAGS) -c $< -o $@

-include $(DEPS)

$(LIBFT_A)		:	FORCE
				$(MAKE) -C $(LIBFT)

FORCE			:

norm			:
				norminette $(SRC_DIR) include

clean			:
				rm -rf $(BUILD_DIR)

fclean			:	clean
				rm -f $(NAME)

re				:	fclean all