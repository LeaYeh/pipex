# Define source files for the main library
MAIN_SRCS	= ft_isalpha.c \
			ft_isdigit.c \
			ft_isalnum.c \
			ft_isascii.c \
			ft_isprint.c \
			ft_isspace.c \
			ft_itoa.c \
			ft_atoi.c \
			ft_split.c \
			ft_toupper.c \
			ft_tolower.c \
			ft_memcmp.c \
			ft_memset.c \
			ft_memcpy.c \
			ft_memccpy.c \
			ft_memmove.c \
			ft_memchr.c \
			ft_bzero.c \
			ft_strncmp.c \
			ft_strlen.c \
			ft_strnlen.c \
			ft_strlcpy.c \
			ft_strlcat.c \
			ft_strchr.c \
			ft_strrchr.c \
			ft_strnstr.c \
			ft_strdup.c \
			ft_substr.c \
			ft_strjoin.c \
			ft_strtrim.c \
			ft_striteri.c \
			ft_strmapi.c \
			ft_calloc.c \
			ft_putchar_fd.c \
			ft_putstr_fd.c \
			ft_putendl_fd.c \
			ft_putnbr_fd.c

# Define source files for the bonus library
BONUS_SRCS	= ft_lstnew.c \
			ft_lstadd_front.c \
			ft_lstsize.c \
			ft_lstlast.c \
			ft_lstadd_back.c \
			ft_lstdelone.c \
			ft_lstclear.c \
			ft_lstiter.c \
			ft_lstmap.c

# Generate object file names (replace file ext from .c to .o) for the main and bonus sources
MAIN_OBJS	= ${MAIN_SRCS:.c=.o}
BONUS_OBJS	= ${BONUS_SRCS:.c=.o}

# Define the name of the library archive
NAME		= libft.a

# Define the compiler and related tools
CC			= cc
AR			= ar
RM			= rm -f

# Define compiler flags
CFLAGS		= -Wall -Wextra -Werror -g

# Define archive creation flags
# 	create, replace with object files and update symbol table
ARFLAGS		= -crs

# Rule to compile .c files into .o files
# 	$< is varible of filename
# 	${<:.c=.o} replace file ext. with filename varible
.c.o:
			${CC} ${CFLAGS} -c $< -o ${<:.c=.o}

# Build the main library
# 	1. list the library depends on MAIN_OBJS files
# 	2. build library with the rule
$(NAME):	${MAIN_OBJS}
			${AR} ${ARFLAGS} ${NAME} ${MAIN_OBJS}

# Default target, build the main library
all:		${NAME}

# Build the bonus library (including main objects)
bonus:		${BONUS_OBJS} ${MAIN_OBJS}
			${AR} ${ARFLAGS} ${NAME} ${BONUS_OBJS} ${MAIN_OBJS}

# Clean up object files
clean:
			${RM} ${MAIN_OBJS} ${BONUS_OBJS}

# Clean up object files and library
fclean:		clean
			${RM} ${NAME}

# Clean and rebuild the library
re:			fclean all

# Define phony targets to avoid conflicts with file names
.PHONY:		all bonus clean fclean re