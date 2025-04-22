.PHONY			:	clean fclean re all norm FORCE bonus

NAME			=   ft_ls
BONUS_NAME		=	ft_ls_bonus

#			GCC

CC				=	cc
CFLAGS			=	-Wall -Wextra -Werror
CFLAGS			+=	-MMD -MP
CFLAGS			+=	-g3
LIBSFLAGS		=	-L$(LIBFT) -lft_ex

#			COMMON

BUILD_DIR		=	.build/
SRC_DIR			=	src/
INCLUDE 		=	-Iinclude/ -I$(LIBFT)/include/

#			SRC

SRC_FILES		=	main				\
					align				\
					clean				\
					data				\
					data2				\
					error				\
					ft_ls				\
					parse				\
					print				\
					recursive			\
					sort				\
					utils				\
					t_lslst/t_lslst		\
					t_lslst/t_lslst2	\

SRC 			= 	$(addprefix $(SRC_DIR), $(addsuffix .c, $(SRC_FILES)))
OBJ 			= 	$(addprefix $(BUILD_DIR), $(addsuffix .o, $(SRC_FILES)))
DEPS 			= 	$(addprefix $(BUILD_DIR), $(addsuffix .d, $(SRC_FILES)))

#			LIBFT

LIBFT			=	libft
LIBFT_A			=	$(LIBFT)/libft_ex.a

#			BONUS

BONUS_BUILD_DIR	=	.build_bonus/
BONUS_SRC_DIR	=	src_bonus/
BONUS_INCLUDE 	=	-Iinclude_bonus/ -I$(LIBFT)/include/

BONUS_SRC_FILES =	$(SRC_FILES)
BONUS_SRC_FILES	+=	

BONUS_SRC 		= 	$(addprefix $(BONUS_SRC_DIR), $(addsuffix .c, $(BONUS_SRC_FILES)))
BONUS_OBJ 		= 	$(addprefix $(BONUS_BUILD_DIR), $(addsuffix .o, $(BONUS_SRC_FILES)))
BONUS_DEPS 		= 	$(addprefix $(BONUS_BUILD_DIR), $(addsuffix .d, $(BONUS_SRC_FILES)))

#			RULES

all				:	$(NAME)
	
$(NAME)			:	$(BUILD_DIR) $(OBJ) $(LIBFT_A)
				$(CC) $(CFLAGS) $(INCLUDE) $(OBJ) $(LIBSFLAGS) -o $(NAME)

$(BUILD_DIR)	:
				mkdir -p $(BUILD_DIR)
				mkdir -p $(BUILD_DIR)t_lslst

$(BUILD_DIR)%.o	: 	$(SRC_DIR)%.c
				$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

-include $(DEPS)

bonus					:	$(BONUS_NAME)

$(BONUS_NAME)			:	$(BONUS_BUILD_DIR) $(BONUS_OBJ) $(LIBFT_A)
						$(CC) $(CFLAGS) $(BONUS_INCLUDE) $(BONUS_OBJ) $(LIBSFLAGS) -o $(BONUS_NAME)

$(BONUS_BUILD_DIR)		:
						mkdir -p $(BONUS_BUILD_DIR)
						mkdir -p $(BONUS_BUILD_DIR)t_lslst

$(BONUS_BUILD_DIR)%.o	: 	$(BONUS_SRC_DIR)%.c
						$(CC) $(CFLAGS) $(BONUS_INCLUDE) -c $< -o $@

-include $(BONUS_DEPS)

$(LIBFT_A)		:	FORCE
				$(MAKE) -C $(LIBFT)

FORCE			:

norm			:
				norminette $(SRC_DIR) include
				norminette $(BONUS_SRC_DIR) include_bonus

clean			:
				rm -rf $(BUILD_DIR)
				rm -rf $(BONUS_BUILD_DIR)

fclean			:	clean
				rm -f $(NAME)
				rm -f $(BONUS_NAME)

re				:	fclean all