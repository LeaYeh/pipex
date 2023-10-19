NAME		:= pipex
INC_DIR		:= include
SRC_DIR		:= source
BUILD_DIR	:= build
COMMON_DIR	:= $(SRC_DIR)/common
MAJOR_DIR	:= $(SRC_DIR)/mandatory
BONUS_DIR	:= $(SRC_DIR)/bonus
LIBFT_DIR	:= $(SRC_DIR)/libft
DPRINTF_DIR	:= $(SRC_DIR)/ftdprintf

COMMON_SRCS	:= error.c \
			free.c \
			utils.c
MAJOR_SRCS	:= pipex.c \
			process.c
BONUS_SRCS	:= pipex.c \
			process.c

COMMON_SRCS := $(addprefix $(COMMON_DIR)/, $(COMMON_SRCS))
MAJOR_SRCS := $(addprefix $(MAJOR_DIR)/, $(MAJOR_SRCS))
BONUS_SRCS := $(addprefix $(BONUS_DIR)/, $(BONUS_SRCS))

COMMON_OBJS := $(patsubst $(COMMON_DIR)/%.c, $(BUILD_DIR)/%.o, $(COMMON_SRCS))
MAJOR_OBJS := $(patsubst $(MAJOR_DIR)/%.c, $(BUILD_DIR)/%.o, $(MAJOR_SRCS))
BONUS_OBJS := $(patsubst $(BONUS_DIR)/%.c, $(BUILD_DIR)/%.o, $(BONUS_SRCS))

CC			= cc
RM			= rm -f

CFLAGS		= -Wall -Wextra -Werror -g -gdwarf-4 -I$(INC_DIR) -I$(LIBFT_DIR) -I$(DPRINTF_DIR)/includes

$(BUILD_DIR)/%.o: $(COMMON_DIR)/%.c
			@mkdir -p $(@D)
			$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/%.o: $(MAJOR_DIR)/%.c
			@mkdir -p $(@D)
			$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/%.o: $(BONUS_DIR)/%.c
			@mkdir -p $(@D)
			$(CC) $(CFLAGS) -c $< -o $@


.PHONY:		all bonus clean fclean re test test_b

$(NAME):	$(COMMON_OBJS) $(MAJOR_OBJS)
			@make -C $(LIBFT_DIR) bonus
			@make -C $(DPRINTF_DIR) all
			$(CC) $(CFLAGS) $(COMMON_OBJS) $(MAJOR_OBJS) $(LIBFT_DIR)/libft.a $(DPRINTF_DIR)/libftdprintf.a -o $(NAME)

all:		$(NAME)

bonus:		$(COMMON_OBJS) $(BONUS_OBJS)
			@make -C $(LIBFT_DIR) bonus
			@make -C $(DPRINTF_DIR) all
			$(CC) $(CFLAGS) $(COMMON_OBJS) $(BONUS_OBJS) $(LIBFT_DIR)/libft.a $(DPRINTF_DIR)/libftdprintf.a -o $(NAME)

clean:
			@make -C $(LIBFT_DIR) clean
			@make -C $(DPRINTF_DIR) clean
			$(RM) $(BUILD_DIR)/*.o

fclean:		clean
			@make -C $(LIBFT_DIR) fclean
			@make -C $(DPRINTF_DIR) fclean
			$(RM) $(NAME)

re: 		fclean all
