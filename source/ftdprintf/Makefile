NAME		= libftdprintf.a
BUILD_DIR	:= build
SRC_DIR		:= srcs
INC_DIR		:= includes
LIBFT_DIR	:= ../libft

MAIN_SRCS	:= ft_printf.c \
			ft_print_char.c \
			ft_print_string.c \
			ft_print_int.c \
			ft_print_uint.c \
			ft_print_addr.c \
			ft_print_hex.c \
			ft_utils.c \
			ft_utoa.c \
			ft_utox.c

MAIN_SRCS := $(addprefix $(SRC_DIR)/, $(MAIN_SRCS))
MAIN_OBJS := $(patsubst $(SRC_DIR)/%.c, $(BUILD_DIR)/%.o, $(MAIN_SRCS))
LIBFT_OBJS	:= $(LIBFT_DIR)/*.o	

# Define the compiler and related tools
CC			= cc
AR			= ar
RM			= rm -f

# Define flags
CFLAGS		= -Wall -Werror -Wextra -I$(INC_DIR) -I$(LIBFT_DIR)
ARFLAGS		= -crs

$(NAME):	$(MAIN_OBJS)
			@make -C $(LIBFT_DIR) bonus
			@cp $(LIBFT_DIR)/*.a $(NAME)
			$(AR) $(ARFLAGS) $(NAME) $(MAIN_OBJS) $(LIBFT_OBJS)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
			@mkdir -p $(@D)
			$(CC) $(CFLAGS) -c $< -o $@

all:		$(NAME)

clean:
			@make -C $(LIBFT_DIR) clean
			$(RM) $(BUILD_DIR)/*.o

fclean:		clean
			@make -C $(LIBFT_DIR) fclean
			$(RM) $(NAME)

test:		$(MAIN_SRCS) $(NAME)
			$(CC) $(CFLAGS) test.c $(MAIN_SRCS) -L$(LIBFT_DIR) -lft -o a.out

test_b:		$(BONUS_SRCS) $(NAME)
			$(CC) $(CFLAGS) test.c $(BONUS_SRCS) -L$(LIBFT_DIR) -lft -o a.out

re:			fclean all

# Define phony targets to avoid conflicts with file names
.PHONY:		all bonus clean fclean re